#pragma once

namespace graphics
{
	class IEngine
	{
	public:
		/// <summary>
		/// Performs system initialization and startup.
		/// </summary>
		virtual void startup() = 0;

		/// <summary>
		/// Performs system shutdown.
		/// </summary>
		virtual void shutdown() = 0;
	};
}

