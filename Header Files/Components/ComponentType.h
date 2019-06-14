#pragma once

enum class ComponentType : int //?????????
{
	COMPONENT_NONE = 0,
	COMPONENT_TRANSFORM = 1 << 0,
	COMPONENT_VELOCITY = 1 << 1,
	COMPONENT_BOXCOLLIDER = 1 << 2,
	COMPONENT_SPHERECOLLIDER = 1 << 3, 
	COMPONENT_GEOMETRY = 1 << 4,
	COMPONENT_TEXTURE = 1 << 5,
	COMPONENT_SHADER = 1 << 6,
	COMPONENT_CAMERA = 1 << 7,
	COMPONENT_LIGHT = 1 << 8,
	COMPONENT_GRAVITY = 1 << 9,
	COMPONENT_AUDIO = 1 << 10,
	COMPONENT_AI = 1 << 11,
	COMPONENT_RAYCOLLIDER =1 << 12,
	COMPONENT_COLLISION = 1 << 13,
	COMPONENT_COLOUR = 1 << 14,
	COMPONENT_WEIGHT = 1 << 15
};

inline ComponentType operator| (const ComponentType& lhs, const ComponentType& rhs) { return static_cast<ComponentType>(static_cast<int>(lhs) | static_cast<int>(rhs)); }

inline ComponentType operator& (const ComponentType& lhs, const ComponentType& rhs) { return static_cast<ComponentType>(static_cast<int>(lhs) & static_cast<int>(rhs)); }

inline ComponentType& operator|= (ComponentType& lhs, const ComponentType& rhs) { return lhs = lhs | rhs; }

inline ComponentType& operator&= (ComponentType& lhs, const ComponentType& rhs) { return lhs = lhs & rhs; }

inline ComponentType operator~(const ComponentType& rhs) { return static_cast<ComponentType>(~static_cast<int>(rhs)); }