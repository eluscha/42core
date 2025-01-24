/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:18:23 by eusatiko          #+#    #+#             */
/*   Updated: 2025/01/24 14:34:45 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PHONEBOOK_H__
#define __PHONEBOOK_H__

#include <iostream>
#include "Contact.hpp"

class PhoneBook
{
    Contact list[8];
    int size;
public:
    PhoneBook();
    void listen();
    
private:
    void add();
    void search(void);
    void exit(void); 
};

std::string check_phone(std::string ph);
int numdigits(int n);
void short_data(std::string data);
int get_idx(std::string input);
void full_data(Contact c);

#endif
