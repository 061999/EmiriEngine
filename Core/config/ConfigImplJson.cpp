#include "Config.h"

#ifdef NDEBUG
#define JSON_HEDLEY_NO_THROW
#endif // NDEBUG

#include <nlohmann/json.hpp>

#include <fstream>

#include <Core/logger/Logger.h>

namespace utl
{
	static constexpr std::array<const char*, CONFIG_TYPE_NUM> JsonKeyMapping
	{
		"FRAME_FLUSH_INT",
		"MAIN_TITLE_STRING",
		"WIDTH_INT",
		"HEIGHT_INT",
		"WINDOW_MAXED_BOOL",
		"IMGUI_INI_STRING",
		"RENDER_VIEW_WIDTH_INT",
		"RENDER_VIEW_HEIGHT_INT",
		"3D_PHYSICA_BUF_SIZE_INT",
	};

	class JsonConfig : public Config
	{
	public:
		JsonConfig() :
			Config{}
		{
			std::ifstream cfg_file{ cfg_path.c_str() };
			if (cfg_file.is_open())
			{
#ifndef NDEBUG
				try
				{
#endif // NDEBUG
					cfg_file >> cfg;
#ifndef NDEBUG
				}
				catch (const std::exception&)
				{
					LOG_ERROR("Read Config File Error");
				}
#endif // NDEBUG
			}
		}

		~JsonConfig() override
		{
			std::ofstream cfg_file{ this->cfg_path.c_str() };
			if (cfg_file.is_open())
			{
#ifndef NDEBUG
				try
				{
#endif // NDEBUG
					cfg_file << cfg;
#ifndef NDEBUG
				}
				catch (const std::exception&)
				{
					LOG_ERROR("Write Config File Error");
				}
#endif // NDEBUG
			}
		}

		//Config
		std::string GetConfigString(CONFIG_TYPE t, const std::string& defval) override
		{
			auto& cur = cfg[JsonKeyMapping[t]];
			if (cur.is_null())
			{
				cur = defval;
				return defval;
			}
			return cur.get<std::string>();
		}

		int GetConfigInt(CONFIG_TYPE t, int defval) override
		{
			auto& cur = cfg[JsonKeyMapping[t]];
			if (cur.is_null())
			{
				cur = defval;
				return defval;
			}
			return cur.get<int>();
		}

		bool GetConfigBool(CONFIG_TYPE t, bool defval) override
		{
			auto& cur = cfg[JsonKeyMapping[t]];
			if (cur.is_null())
			{
				cur = defval;
				return defval;
			}
			return cur.get<bool>();
		}

		void SetConfigString(CONFIG_TYPE t, const std::string& val) override
		{
			auto& cur = cfg[JsonKeyMapping[t]];
			cur = val;
		}

		void SetConfigInt(CONFIG_TYPE t, int val) override
		{
			auto& cur = cfg[JsonKeyMapping[t]];
			cur = val;
		}

		void SetConfigBool(CONFIG_TYPE t, bool val) override
		{
			auto& cur = cfg[JsonKeyMapping[t]];
			cur = val;
		}

		nlohmann::json cfg;
	};

	Config* GetCfg()
	{
		static JsonConfig jcfg{};
		return &jcfg;
	}
}