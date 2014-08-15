#ifndef TMXLAYER_H
#define TMXLAYER_H


#include <string>
#include <map>

class TMXLayer
{
    public:
        TMXLayer();
        TMXLayer(std::string name, int wTiles, int hTiles, int opacity);
        virtual ~TMXLayer();
        std::string  GetName() { return name; };
        int GetWidthInTiles() { return widthInTiles;};
        int GetHeightInTiles() { return heightInTiles; };

        std::map<std::string, std::string> Properties;
    private:
        std::string name;
        int widthInTiles;
        int heightInTiles;
        int opacity;
};

#endif // TMXLAYER_H
