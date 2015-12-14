#pragma once

namespace mdu {

class VisibleGameObject 
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(const std::string &filename);
	virtual void Draw(sf::RenderWindow &window);
	virtual void Update(const float elapsedTime);

	virtual void SetPosition(const float x, const float y);
	virtual sf::Vector2f GetPosition() const;
	virtual bool IsLoaded() const;

	virtual float GetWidth() const;
	virtual float GetHeight() const;

	virtual sf::Rect<float> GetBoundingRect() const;

protected:
	sf::Sprite& GetSprite();

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	std::string m_filename;
	bool m_isLoaded;
};

} //!< end namespace here