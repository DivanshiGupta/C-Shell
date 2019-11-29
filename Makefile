default: main

main: bg_exit.h cd.h exec.h execute_input.h get_input.h ls.h parse_input.h pinfo_pid.h start_init.h str_comp.h print_dirname.h check_redirection1.h parse_pipes.h signal_handler.h ctrlz.h 
	gcc main.c 