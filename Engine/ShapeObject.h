#pragma once
#include "TransformableObject.h"
#include "Bounds.h"

enum ENGINE_API TextureExtensionType
{
	PNG,
	JPG,
	GIF,
};

enum ENGINE_API ShapeObjectType
{
	SOT_CIRCLE,
	SOT_RECTANGLE,
	SOT_CONVEX,
	SOT_VERTEX,

	SOT_COUNT,
};

struct ENGINE_API CircleShapeData
{
	float radius;
	string path;
	IntRect rect;
	size_t pointCount;

	CircleShapeData(const float _radius, const string& _path = "Default", const IntRect& _rect = IntRect(),
					const size_t& _pointCount = 30)
	{
		radius = _radius;
		path = _path;
		rect = _rect;
		pointCount = _pointCount;
	}

	CircleShapeData& operator = (CircleShapeData _other)
	{

		radius = _other.radius;
		path = _other.path;
		rect = _other.rect;
		pointCount = _other.pointCount;

		return *this;
	}
};

struct ENGINE_API RectangleShapeData
{
	Vector2f size;
	string path;
	IntRect rect;
	TextureExtensionType textureType;
	bool isRepeated;

	RectangleShapeData(const Vector2f& _size, const string& _path = "Default", const TextureExtensionType& _textureType = PNG,
					   const bool _isRepeated = false, const IntRect& _rect = IntRect())
	{
		size = _size;
		path = _path;
		rect = _rect;
		textureType = _textureType;
		isRepeated = _isRepeated;
	}
};

struct ENGINE_API ConvexShapeData
{
	vector<Vector2f> point;
	string path;
	IntRect rect;
	TextureExtensionType textureType;
	bool isRepeated;
	ConvexShapeData(const vector<Vector2f> _point, const string& _path, const TextureExtensionType& _textureType
		, const IntRect& _rect = IntRect(), bool _isRepeated = false)
	{
		point = _point;
		path = _path;
		rect = _rect;
		textureType = _textureType;
		isRepeated = _isRepeated;
	}
};

union ENGINE_API ObjectData
{
	CircleShapeData* circleData;
	RectangleShapeData* rectangleData;
	ConvexShapeData* convexData;

	ObjectData() {}
	~ObjectData() {}
};

struct ENGINE_API ShapeObjectData
{
	ShapeObjectType type;
	ObjectData data;

	ShapeObjectData()
	{
		type = SOT_COUNT;
	}
	ShapeObjectData(const ShapeObjectType& _type, const CircleShapeData& _circleData)
	{
		type = _type;
		data.circleData = new CircleShapeData(_circleData);
	}
	ShapeObjectData(const ShapeObjectType& _type, const RectangleShapeData& _rectangleData)
	{
		type = _type;
		data.rectangleData = new RectangleShapeData(_rectangleData);
	}
	ShapeObjectData(const ShapeObjectType& _type, const ConvexShapeData& _convexData)
	{
		type = _type;
		data.convexData = new ConvexShapeData(_convexData);
	}
	~ShapeObjectData()
	{
		if (type == SOT_CIRCLE)
		{
			delete data.circleData;
		}

		else if (type == SOT_RECTANGLE)
		{
			delete data.rectangleData;
		}

		else if (type == SOT_CONVEX)
		{
			delete data.convexData;
		}
	}

	ShapeObjectData& operator = (const ShapeObjectData& _other)
	{
		type = _other.type;

		if (type == SOT_CIRCLE)
		{
			data.circleData = new CircleShapeData(*_other.data.circleData);
		}

		else if (type == SOT_RECTANGLE)
		{
			data.rectangleData = new RectangleShapeData(*_other.data.rectangleData);
		}

		else if (type == SOT_CONVEX)
		{
			data.convexData = new ConvexShapeData(*_other.data.convexData);
		}

		return *this;
	}
};

class ENGINE_API ShapeObject : public TransformableObject
{
	Texture texture;
	Shape* shape;
	ShapeObjectData objectData;

public:
	FORCEINLINE Texture& GetTexture()
	{
		return texture;
	}
	FORCEINLINE ShapeObjectData& GetData()
	{
		return objectData;
	}
	FORCEINLINE virtual Shape* GetDrawable() const override
	{
		return shape;
	}
	FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
	{
		shape->setOrigin(_origin);
	}
	FORCEINLINE virtual void SetLocation(const Vector2f& _position) override
	{
		shape->setPosition(_position);
	}
	FORCEINLINE virtual void SetRotation(const Angle& _rotation) override
	{
		shape->setRotation(_rotation);
	}
	FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
	{
		shape->setScale(_scale);
	}
	FORCEINLINE virtual void SetTransform(const TransformData& _transformData) override
	{
		shape->setOrigin(_transformData.origin);
		shape->setPosition(_transformData.position);
		shape->setRotation(_transformData.rotation);
		shape->setScale(_transformData.scale);
	}
	FORCEINLINE virtual void Move(const Vector2f& _offset) override
	{
		shape->move(_offset);
	}
	FORCEINLINE virtual void Rotate(const Angle& _angle) override
	{
		shape->rotate(_angle);
	}
	FORCEINLINE virtual void Scale(const Vector2f& _factor) override
	{
		shape->scale(_factor);
	}

public:
	ShapeObject(const CircleShapeData& _data);
	ShapeObject(const RectangleShapeData& _data);
	ShapeObject(const ConvexShapeData& _data);
	ShapeObject(const ShapeObject& _other);
	~ShapeObject();

private:
	void InitCircle(const CircleShapeData& _data);
	void InitRectangle(const RectangleShapeData& _data);
	void InitConvex(const ConvexShapeData& _data);
};