/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:13:50 by dabae             #+#    #+#             */
/*   Updated: 2024/05/15 15:20:17 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv)
{
	int	pipe[2];

	//PSEUDO CODE
	//1. read input
	//2. parse input(make parsing tree)
	//2-1. if input is exit, exit
	//2-2. if input is cd, change directory
	//2-3. if input is env, print environment
	//2-4. if input is setenv, set environment
	//2-5. if input is unsetenv, unset environment
	//2-6. if input is other command, execute command
	//3. execute command
	//3-1. if command is built-in, execute built-in
	//3-2. if command is not built-in, execute command
	//4. free memory
	//5. loop
	return (0);
}