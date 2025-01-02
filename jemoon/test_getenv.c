/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_getenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:44:22 by jemoon            #+#    #+#             */
/*   Updated: 2024/12/30 21:21:22 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  <stdlib.h>
#include  <stdio.h>
 
/* Where the environment variable 'PATH' is set to a value. */
 
int main(void)
{
   char *pathvar;
 
   pathvar = getenv("PATH");
   printf("%s",pathvar);
}