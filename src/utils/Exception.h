/* 
 * File:   TwException.h
 * Author: masum
 *
 * Created on April 7, 2013, 8:49 PM
 */

#ifndef EXCEPTION_H
#define	EXCEPTION_H

#include <string>
#include <exception>

class Exception : public std::exception{
public:
    Exception(std::string ss) : msg(ss) {};
    virtual const char* what() const throw() { return msg.c_str(); };
    virtual ~Exception() throw(){};
protected:
    std::string msg;
};


#endif	/* EXCEPTION_H */



