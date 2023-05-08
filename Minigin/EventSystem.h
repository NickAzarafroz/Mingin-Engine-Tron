#pragma once
#include <cstdint>

namespace dae
{
	enum EventType
	{
		PLAYER_HURT,
		PLAYER_SCORED
	};

	enum Type
	{
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_BOOL
	};

	struct EventArg
	{
		Type m_ArgType;
	};

	struct Event
	{
		static const uint8_t MAX_ARGS = 8;

		EventType m_Type;
		uint8_t m_NumArgs;
		EventArg m_Args[MAX_ARGS];
	};
}