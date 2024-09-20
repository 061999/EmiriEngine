#pragma once
#include <common_header.h>
#include <utl/async.h>
#include <utl/math.h>

namespace input
{
	enum axis
	{
		x = 0u,
		y = 1u,
		z = 2u,
	};

	// enum modifier_key : u32
	// {
	// 	none = 0x00000000u,
	// 	left_shift  = 0x00000001u,
	// 	right_shift = 0x00000002u,
	// 	left_ctrl   = 0x00000004u,
	// 	right_ctrl  = 0x00000008u,
	// 	left_alt    = 0x00000010u,
	// 	right_alt   = 0x00000020u,
	// 	shift = left_shift | right_shift,
	// 	ctrl = left_ctrl | right_ctrl,
	// 	alt = left_alt | right_alt,
	// };

	enum input_code : u32
	{
		mouse_position_x,
		mouse_position_y,
		mouse_position,

		mouse_left,
		mouse_right,
		mouse_middle,
		mouse_wheel,
		mouse_x1,
		mouse_x2,

		vk_backspace,
		vk_tab,
		vk_return,

		vk_shift,
		vk_left_shift,
		vk_right_shift,
		vk_ctrl,
		vk_left_ctrl,
		vk_right_ctrl,
		vk_alt,
		vk_left_alt,
		vk_right_alt,
		vk_capslock,
		vk_escape,
		vk_space,
		vk_page_up,
		vk_page_down,
		vk_home,
		vk_end,
		vk_left,
		vk_up,
		vk_right,
		vk_down,
		vk_pause,
		vk_print_screen,
		vk_delete,
		vk_insert,

		vk_0,
		vk_1,
		vk_2,
		vk_3,
		vk_4,
		vk_5,
		vk_6,
		vk_7,
		vk_8,
		vk_9,

		vk_a,
		vk_b,
		vk_c,
		vk_d,
		vk_e,
		vk_f,
		vk_g,
		vk_h,
		vk_i,
		vk_j,
		vk_k,
		vk_l,
		vk_m,
		vk_n,
		vk_o,
		vk_p,
		vk_q,
		vk_r,
		vk_s,
		vk_t,
		vk_u,
		vk_v,
		vk_w,
		vk_x,
		vk_y,
		vk_z,

		vk_numpad_0,
		vk_numpad_1,
		vk_numpad_2,
		vk_numpad_3,
		vk_numpad_4,
		vk_numpad_5,
		vk_numpad_6,
		vk_numpad_7,
		vk_numpad_8,
		vk_numpad_9,

		vk_multiply,
		vk_add,
		vk_subtract,
		vk_decimal,
		vk_devide,

		vk_f1,
		vk_f2,
		vk_f3,
		vk_f4,
		vk_f5,
		vk_f6,
		vk_f7,
		vk_f8,
		vk_f9,
		vk_f10,
		vk_f11,
		vk_f12,

		vk_numlock,
		vk_scrollock,

		window_resize,

		max
	};

	enum input_type : u32
	{
		keyboard,
		mouse,
		controler,
		raw,
		count,
	};

	struct input_value
	{
		DirectX::XMFLOAT3 previous;
		DirectX::XMFLOAT3 current;
	};

	struct input_source
	{
		u64            binding{ 0ul };
		input_type     source_type{};
		u32            code{ 0 };
		float          multiplier{ 0 };
		bool           is_discrete{ true };
		axis           source_axis{};
		axis           _axis{};
		//modifier_key   modifier{};
	};

	void get_input(input_type type, input_code code, input_value& value);

	void set_input(input_type type, input_code code, DirectX::XMFLOAT3 value);

	void register_controler_process();

	namespace detail
	{
		class input_system_base
		{
		private:
		protected:
			input_system_base();
			virtual ~input_system_base();
		public:
			virtual void on_event(input_type, input_code, const input_value&) = 0;
		};

	}
}