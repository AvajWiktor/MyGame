#pragma once
class Button
{
public:
	Button(std::string path1, std::string path2, uint8_t type, sf::Vector2f position, sf::Vector2f scale)
	{
		BtnTextureOn_.loadFromFile(path1);
		BtnTextureOff_.loadFromFile(path2);
		BtnSprite_.setTexture(BtnTextureOff_);
		BtnSprite_.setOrigin(BtnTextureOff_.getSize().x / 2.0, BtnTextureOff_.getSize().y / 2.0);
		BtnSprite_.setScale(scale);
		BtnSprite_.setPosition(position);
		BtnType_ = type;
	}
	Button(std::string path1, std::string path2, uint8_t type, sf::Vector2u resolution, sf::Vector2f position, sf::Vector2f scale)
	{
		BtnTextureOn_.loadFromFile(path1);
		BtnTextureOff_.loadFromFile(path2);
		BtnSprite_.setTexture(BtnTextureOff_);
		BtnSprite_.setOrigin(BtnTextureOff_.getSize().x / 2.0, BtnTextureOff_.getSize().y / 2.0);
		BtnSprite_.setScale(scale);
		BtnSprite_.setPosition(position);
		BtnType_ = type;
		Resolution_ = resolution;

	}
	sf::Vector2u getResolution()
	{
		return Resolution_;
	}
	bool isButtonPressed(sf::Vector2f mousePos)
	{
		
		if (BtnSprite_.getGlobalBounds().contains(mousePos))
		{
			BtnSprite_.setTexture(BtnTextureOn_);
			if (!(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)))
			{
				
				IsPressedFlag = false;
				return false;
			}
			if((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) && (!(IsPressedFlag)))
			{
				IsPressedFlag = true;
				
				return true;
				
			}
			else
			{
				return false;
			}
			
			
		}
		else
		{
			BtnSprite_.setTexture(BtnTextureOff_);
			return false;
		}
	}
	uint8_t getType()
	{
		return BtnType_;
	}
	sf::Sprite getButton()
	{
		return BtnSprite_;
	}
private:
	sf::Sprite BtnSprite_;
	sf::Texture BtnTextureOn_, BtnTextureOff_;
	uint8_t BtnType_ = 0;
	bool IsPressedFlag = true;
	sf::Vector2u Resolution_ = sf::Vector2u(0, 0);

};