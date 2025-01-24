/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:17:03 by eusatiko          #+#    #+#             */
/*   Updated: 2025/01/24 14:35:38 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CONTACT_H__
#define __CONTACT_H__

#include <string>

class Contact
{
    std::string first_name, last_name, nickname, phone, secret;

public:

    Contact();
    Contact(std::string fn, std::string ln, std::string nn, std::string ph, std::string sc);

    std::string get_first_name();
    std::string get_last_name();
    std::string get_nickname();
    std::string get_phone();
    std::string get_secret();
};

#endif
