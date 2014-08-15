#include "Texture.h"
#include "TextureManager.h"

Texture::Texture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;

	if (TextureManager::IsRendererSet())
		renderer = TextureManager::GetRenderer();
	else
	{
		printf ("Error TextureManager has no renderer set. Use \"TextureManager::SetRenderer()\" before adding textures in the manager to fix. \n");
	}
}

Texture::Texture(std::string path)
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;

	if (TextureManager::IsRendererSet())
	{
		renderer = TextureManager::GetRenderer();
		loadFromFile(path);
	}
	else
	{
		printf ("Error TextureManager has no renderer set. Use \"TextureManager::SetRenderer()\" before adding textures in the manager to fix. \n");
	}
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else if (renderer == NULL)
	{
		printf( "Unable to load image %s! Texture.renderer not assigned.\n", path.c_str());
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	path = texPath;
	mTexture = newTexture;
	return mTexture != NULL;
}


int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}

void Texture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		renderer = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void Texture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void Texture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
}

void Texture::renderDest( int x, int y, SDL_Rect* clip, SDL_Rect* dest, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	dest->x = x;
	dest->y = y;


	//Render to screen
	SDL_RenderCopyEx( renderer, mTexture, clip, dest, angle, center, flip );
}