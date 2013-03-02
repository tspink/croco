__cmdline_opt_start = ADDR(.cmdline_opt);
__cmdline_opt_size = SIZEOF(.cmdline_opt);
__cmdline_opt_end = ADDR(.cmdline_opt) + SIZEOF(.cmdline_opt);

__cmdline_opt_ptr_start = ADDR(.cmdline_opt_ptr);
__cmdline_opt_ptr_size = SIZEOF(.cmdline_opt_ptr);
__cmdline_opt_ptr_end = ADDR(.cmdline_opt_ptr) + SIZEOF(.cmdline_opt_ptr);
