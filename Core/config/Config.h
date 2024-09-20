#pragma once

#include <string>

namespace utl
{
	enum CONFIG_TYPE
	{
		CONFIG_TYPE_FRAME_FLUSH_INT,
		CONFIG_TYPE_MAIN_TITLE_STRING,
		CONFIG_TYPE_WIDTH_INT,
		CONFIG_TYPE_HEIGHT_INT,
		CONFIG_TYPE_WINDOW_MAXED_BOOL,
		CONFIG_TYPE_IMGUI_INI_STRING,
		CONFIG_TYPE_RENDER_VIEW_WIDTH_INT,
		CONFIG_TYPE_RENDER_VIEW_HEIGHT_INT,

		CONFIG_TYPE_3D_PHYSICA_BUF_SIZE_INT,
		CONFIG_TYPE_NUM,
	};

	class Config
	{
	public:
		virtual std::string GetConfigString(CONFIG_TYPE t, const std::string& defval) = 0;
		virtual int GetConfigInt(CONFIG_TYPE t, int defval) = 0;
		virtual bool GetConfigBool(CONFIG_TYPE t, bool defval) = 0;

		virtual void SetConfigString(CONFIG_TYPE t, const std::string& val) = 0;
		virtual void SetConfigInt(CONFIG_TYPE t, int val) = 0;
		virtual void SetConfigBool(CONFIG_TYPE t, bool val) = 0;

		Config() :
			cfg_path{ "Py.config" }
		{}
		virtual ~Config() = default;
		
		std::string cfg_path;
	};

	Config* GetCfg();

	template<typename T>
	inline T GetConfig(CONFIG_TYPE t, const T& defval)
	{
		static_assert(false, "dont have this type cfg");
		return T{};
	}

	template<>
	inline std::string GetConfig(CONFIG_TYPE t, const std::string& defval)
	{
		return GetCfg()->GetConfigString(t, defval);
	}

	template<>
	inline int GetConfig(CONFIG_TYPE t, const int& defval)
	{
		return GetCfg()->GetConfigInt(t, defval);
	}

	template<>
	inline bool GetConfig(CONFIG_TYPE t, const bool& defval)
	{
		return GetCfg()->GetConfigBool(t, defval);
	}

	template<typename T>
	inline void SetConfig(CONFIG_TYPE t, const T& val)
	{
		static_assert(false, "dont have this type");
	}

	template<>
	inline void SetConfig(CONFIG_TYPE t, const std::string& val)
	{
		GetCfg()->SetConfigString(t, val);
	}

	template<>
	inline void SetConfig(CONFIG_TYPE t, const int& val)
	{
		GetCfg()->SetConfigInt(t, val);
	}

	template<>
	inline void SetConfig(CONFIG_TYPE t, const bool& val)
	{
		GetCfg()->SetConfigBool(t, val);
	}
}