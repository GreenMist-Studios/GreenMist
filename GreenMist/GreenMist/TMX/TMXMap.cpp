#include "TMXMap.h"

TMXMap::TMXMap()
{
    //ctor
}

TMXMap::~TMXMap()
{
    //dtor
}

// trim from start
std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

#define TCHAR char    //Not unicode
#define TEXT(x) x     //Not unicode
#define DWORD long
#define BYTE unsigned char

const static TCHAR padCharacter = TEXT('=');
std::vector<BYTE> base64Decode(const std::basic_string<TCHAR>& input)
{
	if (input.length() % 4) //Sanity check
		throw std::runtime_error("Non-Valid base64!");
	size_t padding = 0;
	if (input.length())
	{
		if (input[input.length()-1] == padCharacter)
			padding++;
		if (input[input.length()-2] == padCharacter)
			padding++;
	}
	//Setup a vector to hold the result
	std::vector<BYTE> decodedBytes;
	decodedBytes.reserve(((input.length()/4)*3) - padding);
	DWORD temp=0; //Holds decoded quanta
	std::basic_string<TCHAR>::const_iterator cursor = input.begin();
	while (cursor < input.end())
	{
		for (size_t quantumPosition = 0; quantumPosition < 4; quantumPosition++)
		{
			temp <<= 6;
			if       (*cursor >= 0x41 && *cursor <= 0x5A) // This area will need tweaking if
				temp |= *cursor - 0x41;		              // you are using an alternate alphabet
			else if  (*cursor >= 0x61 && *cursor <= 0x7A)
				temp |= *cursor - 0x47;
			else if  (*cursor >= 0x30 && *cursor <= 0x39)
				temp |= *cursor + 0x04;
			else if  (*cursor == 0x2B)
				temp |= 0x3E; //change to 0x2D for URL alphabet
			else if  (*cursor == 0x2F)
				temp |= 0x3F; //change to 0x5F for URL alphabet
			else if  (*cursor == padCharacter) //pad
			{
				switch( input.end() - cursor )
				{
				case 1: //One pad character
					decodedBytes.push_back((temp >> 16) & 0x000000FF);
					decodedBytes.push_back((temp >> 8 ) & 0x000000FF);
					return decodedBytes;
				case 2: //Two pad characters
					decodedBytes.push_back((temp >> 10) & 0x000000FF);
					return decodedBytes;
				default:
					throw std::runtime_error("Invalid Padding in Base 64!");
				}
			}  else
				throw std::runtime_error("Non-Valid Character in Base 64!");
			cursor++;
		}
		decodedBytes.push_back((temp >> 16) & 0x000000FF);
		decodedBytes.push_back((temp >> 8 ) & 0x000000FF);
		decodedBytes.push_back((temp      ) & 0x000000FF);
	}
	return decodedBytes;
}

/* report a zlib or i/o error */
inline void zerr(int ret)
{
switch (ret) {
case Z_ERRNO:
    if (ferror(stdin))
        fputs("error reading stdin\n", stderr);
    if (ferror(stdout))
        fputs("error writing stdout\n", stderr);
    break;
case Z_STREAM_ERROR:
    fputs("invalid compression level\n", stderr);
    break;
case Z_DATA_ERROR:
    fputs("invalid or incomplete deflate data\n", stderr);
    break;
case Z_MEM_ERROR:
    fputs("out of memory\n", stderr);
    break;
case Z_VERSION_ERROR:
    fputs("zlib version mismatch!\n", stderr);
}
}

bool gzipInflate( const std::vector<unsigned char> compressedBytes, std::vector<unsigned char> &uncompressedBytes ) {
  if ( compressedBytes.size() == 0 ) {
    uncompressedBytes = compressedBytes;
    return true ;
  }

  uncompressedBytes.clear() ;

  unsigned full_length = compressedBytes.size() ;
  unsigned half_length = compressedBytes.size() / 2;

  unsigned uncompLength = full_length ;
  char* uncomp = (char*) calloc( sizeof(char), uncompLength );

  z_stream strm;
  strm.next_in = (Bytef*) &*compressedBytes.begin();
  strm.avail_in = compressedBytes.size() ;
  strm.total_out = 0;
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;

  bool done = false ;

  if (inflateInit2(&strm, (16+MAX_WBITS)) != Z_OK) {
    free( uncomp );
    return false;
  }

  while (!done) {
    // If our output buffer is too small
    if (strm.total_out >= uncompLength ) {
      // Increase size of output buffer
      char* uncomp2 = (char*) calloc( sizeof(char), uncompLength + half_length );
      memcpy( uncomp2, uncomp, uncompLength );
      uncompLength += half_length ;
      free( uncomp );
      uncomp = uncomp2 ;
    }

    strm.next_out = (Bytef *) (uncomp + strm.total_out);
    strm.avail_out = uncompLength - strm.total_out;

    // Inflate another chunk.
    int err = inflate (&strm, Z_SYNC_FLUSH);
    if (err == Z_STREAM_END) done = true;
    else if (err != Z_OK)  {
      break;
    }
  }

  if (inflateEnd (&strm) != Z_OK) {
    free( uncomp );
    return false;
  }

  for ( size_t i=0; i<strm.total_out; ++i ) {
    uncompressedBytes.push_back((unsigned char)uncomp[ i ]);
  }
  free( uncomp );
  return true ;
}


int ReadProperties(XMLElement* element, std::map<std::string,std::string>& destProperties)
{
    int c = 0;
    XMLElement* propertyListElement = element->FirstChildElement("properties");

    if (propertyListElement == NULL)
        return 0;

    for (XMLElement* propertyElement = propertyListElement->FirstChildElement("property"); propertyElement != NULL; propertyElement = propertyElement->NextSiblingElement("property"))
    {
        destProperties.insert(std::pair<std::string,std::string>(propertyElement->Attribute("name"),propertyElement->Attribute("value")));
        c++;
    }

    return c;
}

void ReadPoints(char* input,Vector2 Position, std::vector<Vector2>& Points)
{
    char* x = strtok(input, " ,");
    char* y = strtok(NULL, " ,");
    Points.push_back(Position + Vector2(atoi(x),atoi(y)));

    while(x != NULL && y!=NULL)
    {
        x = strtok(NULL, " ,");
        y = strtok(NULL, " ,");
        Points.push_back(Position + Vector2(atoi(x),atoi(y)));
    }
}

bool TMXMap::Load(SDL_Renderer* renderer, std::string directory)
{
	XMLDocument doc;
	doc.LoadFile(directory.c_str());

//READ IN MAP SETTINGS
    XMLElement* mapelement = doc.FirstChildElement("map");

    Version = mapelement->Attribute("version");
    Orientation = mapelement->Attribute("orientation");
    WidthInTiles = mapelement->IntAttribute("width");
    HeightInTiles = mapelement->IntAttribute("height");
    TileWidth = mapelement->IntAttribute("tilewidth");
    TileHeight = mapelement->IntAttribute("tileheight");


    ReadProperties(mapelement, Properties);

//READ in Tilesets
    XMLElement* currentnode;
    TMXTileset* tmpTileset = new TMXTileset();

    XMLElement* restoreElement;
    for (currentnode = mapelement->FirstChildElement("tileset"); currentnode != NULL; currentnode = currentnode->NextSiblingElement("tileset"))
    {
        restoreElement = currentnode;
        XMLElement* imageElement = currentnode->FirstChildElement("image");
        tmpTileset->Initialize(renderer, currentnode->IntAttribute("firstgid"), currentnode->Attribute("name"),
                                currentnode->IntAttribute("tilewidth"),  currentnode->IntAttribute("tileheight"),
                                imageElement->Attribute("source"), imageElement->IntAttribute("width"),imageElement->IntAttribute("height")
                                );

        int imageWidthInTiles = tmpTileset->GetImageWidth()/tmpTileset->GetTileWidth();
        int imageHeightInTiles = tmpTileset->GetImageHeight()/tmpTileset->GetTileHeight();

        for (int i=0; i < imageHeightInTiles; i++)
        {
            for (int j=0; j < imageWidthInTiles; j++)
            {
                SDL_Rect rect;
                rect.x = j * tmpTileset->GetTileWidth();
                rect.y = i * tmpTileset->GetTileHeight();
                rect.w = tmpTileset->GetTileWidth();
                rect.h = tmpTileset->GetTileHeight();
                tmpTileset->GidRectangles.insert(std::pair<int,SDL_Rect>(tmpTileset->GetFirstGid()+ i * (imageWidthInTiles) + j, rect));
            }
        }
        Tilesets.push_back(tmpTileset);
    }
    currentnode = restoreElement;


//Read Tile Layers or Object Group
    TMXLayer* tmpLayer;
    XMLElement* tmpElement;

    while (((tmpElement = currentnode->NextSiblingElement()) != NULL) && (strcmp(tmpElement->Name(), "layer") == 0 || strcmp(tmpElement->Name(), "objectgroup") == 0))
    {
        currentnode = tmpElement;
    //Read Tile Layers
        if (strcmp(tmpElement->Name(), "layer") == 0)
        {

            tmpLayer = new TMXTileLayer(currentnode->Attribute("name"), currentnode->IntAttribute("width"), currentnode->IntAttribute("height"),0);


            ReadProperties(tmpElement, tmpLayer->Properties);

            XMLElement* dataElement = currentnode->FirstChildElement("data");

            const char* encoding = dataElement->Attribute("encoding");
            const char* compression = dataElement->Attribute("compression");

            if (encoding == NULL)
            {
                XMLElement* tileElement = dataElement->FirstChildElement("tile");

                int gid = tileElement->IntAttribute("gid");
                int count = 0;

                size_t k = 0;
                while (k < Tilesets.size() && gid > Tilesets[k]->GetLastGid())
                    k++;

                if (gid != 0)
                        ((TMXTileLayer*) tmpLayer)->Tiles.push_back(new Tile(gid, k, Vector2(count%WidthInTiles * TileWidth, count/WidthInTiles*TileHeight)));
                printf("%d", gid);
                while (((tileElement = tileElement->NextSiblingElement("tile")) != NULL))
                {
                    gid = tileElement->IntAttribute("gid");
                    while (gid < Tilesets[k]->GetFirstGid() || gid > Tilesets[k]->GetLastGid())
                    k++;

                    if (gid != 0){
                        ((TMXTileLayer*) tmpLayer)->Tiles.push_back(new Tile(gid,k, Vector2(count%WidthInTiles * TileWidth, count/WidthInTiles*TileHeight)));
                    printf("%d (%d,%d)\n", gid,count%WidthInTiles * TileWidth, count/WidthInTiles*TileHeight);
                    }
                    count++;
                }

            }
            else if (strcmp(encoding, "base64") == 0)
            {

                std::string CleanText = dataElement->GetText();
                CleanText = trim(CleanText);

                std::vector<unsigned char> decodedList = base64Decode(CleanText);
                int dListSize = decodedList.size();
                long unsigned int uncompressedSize = (long unsigned int)(HeightInTiles * WidthInTiles * 4);

                if (compression == NULL)
                {
                        int m_LayerRow = 0;
                        int m_LayerCol = 0;
                        int sizes = decodedList.size();
                        for( int i = 0; i < sizes - 3; i += 4 )
                        {
                            const int gid = decodedList[i] | decodedList[i + 1] << 8 | decodedList[i + 2] << 16 | decodedList[i + 3] << 24;

                            int k = 0;
                            while (Tilesets[k] != NULL && gid > Tilesets[k]->GetLastGid())
                                k++;

                            if (gid != 0)
                                ((TMXTileLayer*) tmpTileset)->Tiles.push_back(new Tile(gid, k, Vector2(m_LayerCol*TileWidth, m_LayerRow*TileHeight)));

                            m_LayerCol++;

                            if ( m_LayerCol == WidthInTiles )
                            {
                                m_LayerCol = 0;
                                m_LayerRow++;
                            }
                        }
                }
                else if (strcmp(compression, "zlib") == 0)
                {
                    long unsigned int decodedListSize = (long unsigned int) dListSize;
                    unsigned char* decodedArray = &*decodedList.begin();

                    Bytef* uncompressedArray = (Bytef*) malloc(uncompressedSize * sizeof(Bytef));
                    zerr(uncompress(uncompressedArray, &uncompressedSize, decodedArray, decodedListSize));

                    int m_LayerRow = 0;
                    int m_LayerCol = 0;

                    for( int i = 0; i < uncompressedSize - 3; i += 4 )
                    {
                        const int gid = uncompressedArray[i] | uncompressedArray[i + 1] << 8 | uncompressedArray[i + 2] << 16 | uncompressedArray[i + 3] << 24;

                        int k = 0;
                        while (k < Tilesets.size() && gid > Tilesets[k]->GetLastGid())
                            k++;

                        if (gid != 0)
                            ((TMXTileLayer*)tmpLayer)->Tiles.push_back(new Tile(gid,k, Vector2(m_LayerCol*TileWidth, m_LayerRow*TileHeight)));

                        m_LayerCol++;

                        if ( m_LayerCol == WidthInTiles )
                        {
                            m_LayerCol = 0;
                            m_LayerRow++;
                        }
                    }
                }
                else if (strcmp(compression, "gzip") == 0)
                {
                    std::vector<unsigned char> uncompressedArray;
                    if (gzipInflate(decodedList,uncompressedArray))
                    {
                        int m_LayerRow = 0;
                        int m_LayerCol = 0;

                        for( int i = 0; i < uncompressedSize - 3; i += 4 )
                        {
                            const int gid = uncompressedArray[i] | uncompressedArray[i + 1] << 8 | uncompressedArray[i + 2] << 16 | uncompressedArray[i + 3] << 24;

                            int k = 0;
                            while (Tilesets[k] != NULL && gid > Tilesets[k]->GetLastGid())
                                k++;

                            if (gid != 0)
                                ((TMXTileLayer*) tmpLayer)->Tiles.push_back(new Tile(gid, k, Vector2(m_LayerCol*TileWidth, m_LayerRow*TileHeight)));

                            m_LayerCol++;

                            if ( m_LayerCol == WidthInTiles )
                            {
                                m_LayerCol = 0;
                                m_LayerRow++;
                            }
                        }
                    }
                }
            }
            else if (strcmp(encoding, "csv") == 0)
            {

                std::string CleanText = dataElement->GetText();
                CleanText = trim(CleanText);

                std::string::size_type k = 0;
                while((k=CleanText.find(',',k))!=CleanText.npos) {
                    CleanText.erase(k, 1);
                }

                const char* charText = CleanText.c_str();

                int m_LayerRow = 0;
                int m_LayerCol = 0;
                for (int i = 0; charText[i] != NULL; i++ )
                {
                    int gid = charText[i] - '0';

                    int k = 0;
                    while (Tilesets[k] != NULL && gid > Tilesets[k]->GetLastGid())
                        k++;

                    if (gid != 0)
                        ((TMXTileLayer*) tmpLayer)->Tiles.push_back(new Tile(gid,k, Vector2(m_LayerCol*TileWidth, m_LayerRow*TileHeight)));

                    m_LayerCol++;

                    if ( m_LayerCol == WidthInTiles )
                    {
                        m_LayerCol = 0;
                        m_LayerRow++;
                    }
                }
            }
            Layers.push_back(tmpLayer);
            TileLayers.push_back((TMXTileLayer*)tmpLayer);
        }
        //Read Object Layers
        else if (strcmp(tmpElement->Name(), "objectgroup") == 0)
        {
            int o=255;
            tmpLayer = new TMXObjectGroupLayer(currentnode->Attribute("name"), currentnode->IntAttribute("width"), currentnode->IntAttribute("height"),o);
            SDL_Color color;
            if (currentnode->Attribute("color") != NULL )
            {
                std::string tmpstr = std::string(currentnode->Attribute("color"));
                tmpstr.erase(0,1);
                std::transform(tmpstr.begin(), tmpstr.end(),tmpstr.begin(), ::toupper);
                std::string hex_alphabets = std::string("0123456789ABCDEF");
                int val[3];
                int k = 0,int1 = 0, int2 = 0;
                for(int i=0;i<6;i+=2) {
                    int1 = hex_alphabets.find(tmpstr[i]);
                    int2 = hex_alphabets.find(tmpstr[i+1]);
                    val[k] = (int1 * 16) + int2;
                    k++;
                }
                color.a = 255;
                color.r = val[0];
                color.g = val[1];
                color.b = val[2];
            }
            else
            {
                color.r = color.g = color.b =255;
            }

            ((TMXObjectGroupLayer*) tmpLayer)->Color = color;

            ReadProperties(tmpElement, tmpLayer->Properties);

            for (tmpElement = tmpElement->FirstChildElement("object"); tmpElement != NULL; tmpElement = tmpElement->NextSiblingElement("object") )
            {
                Object* o = new Object(Vector2(tmpElement->IntAttribute("x"),tmpElement->IntAttribute("y")), tmpElement->IntAttribute("width"),tmpElement->IntAttribute("height"));

                if (tmpElement->IntAttribute("gid") != 0)
                {
                    o->Type = tmpElement->Attribute("type");
                    o->ObjectType = TileType;
                    o->SetGid(tmpElement->IntAttribute("gid"));
                    ((TMXObjectGroupLayer*) tmpLayer)->Objects.push_back(o);
                }
                else if (tmpElement->FirstChildElement("ellipse")!= NULL)
                {
                    o->Type = tmpElement->Attribute("type");
                    o->ObjectType = Ellipse;
                    ((TMXObjectGroupLayer*) tmpLayer)->Objects.push_back(o);
                }
                else if (tmpElement->FirstChildElement("polygon")!= NULL)
                {
                    o->Type = tmpElement->Attribute("type");
                    o->ObjectType = Polygon;
                    ReadPoints((char*)tmpElement->FirstChildElement("polygon")->Attribute("points"), o->GetPosition(), o->Points);
                    ((TMXObjectGroupLayer*) tmpLayer)->Objects.push_back(o);
                }
                else if (tmpElement->FirstChildElement("polyline")!= NULL)
                {
                    o->Type = tmpElement->Attribute("type");
                    o->ObjectType = PolyLine;
                    ReadPoints((char*)tmpElement->FirstChildElement("polyline")->Attribute("points"),o->GetPosition(), o->Points);
                    ((TMXObjectGroupLayer*) tmpLayer)->Objects.push_back(o);
                }
                else
                {
                    o->Type = tmpElement->Attribute("type");
                    o->ObjectType = Rectangle;
                    ((TMXObjectGroupLayer*) tmpLayer)->Objects.push_back(o);
                }
            }
            Layers.push_back(tmpLayer);
            ObjectGroupLayers.push_back((TMXObjectGroupLayer*)tmpLayer);
        }
    }

    return true;
}
