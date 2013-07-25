/******************************************************************* 
 * C file generated by Protoc for Embedded C.                      *
 * Version 1.0M4 (2013-03-31)                                      *
 *                                                                 *
 * Copyright (c) 2009-2013                                         *
 * Technische Universitaet Muenchen                                *
 * http://www4.in.tum.de/                                          *
 *                                                                 *
 * Source : hello.proto
 *                                                                 *
 * Do not edit.                                                    *
 *******************************************************************/
 
#include "Hello.h"

/*******************************************************************
 * Message: Hello.proto, line 3
 *******************************************************************/

void Hello_clear(struct Hello *_Hello) {
	_memset(_Hello, 0, sizeof(struct Hello));
}

void Hello_init_optional_attributes(struct Hello *_Hello) {
	_Hello->_counter = 0;
	
}

int Hello_is_default_message(struct Hello *_Hello) {
    return _Hello->_counter == 0
    ;
}

int Hello_write(struct Hello *_Hello, void *_buffer, int offset) {
	/* Write content of each message element.*/
	/* Write the optional attribute only if it is different than the default value. */
	if(_Hello->_counter != 0) {
		offset = write_raw_varint32((1<<3)+0, _buffer, offset);
	    offset = write_raw_varint32(_Hello->_counter, _buffer, offset);
	}
	
	return offset;
}

int Hello_write_with_tag(struct Hello *_Hello, void *_buffer, int offset, int tag) {
	/* Write tag.*/
	offset = write_raw_varint32((tag<<3)+2, _buffer, offset);
	/* Write content.*/
	offset = Hello_write_delimited_to(_Hello, _buffer, offset);
	
	return offset;
}

int Hello_write_delimited_to(struct Hello *_Hello, void *_buffer, int offset) {
	int i, shift, new_offset, size;
	
	new_offset = Hello_write(_Hello, _buffer, offset);
	size = new_offset - offset;
	shift = (size > 127) ? 2 : 1;
	for (i = new_offset - 1; i >= offset; -- i)
	    *((char *)_buffer + i + shift) = *((char *)_buffer + i);
	
	write_raw_varint32((unsigned long) size, _buffer, offset);         
	    
	return new_offset + shift;
}

int Hello_read(void *_buffer, struct Hello *_Hello, int offset, int limit) {
	unsigned int i = 0;
	unsigned long long value = i;
	unsigned long tag = value;
	
	/* Reset all attributes to 0 in advance. */
	Hello_clear(_Hello);
	/* Assign the optional attributes. */
	Hello_init_optional_attributes(_Hello);
	
	/* Read/interpret all attributes from buffer offset until upper limit is reached. */
	while(offset < limit) {
	    offset = read_raw_varint32(&tag, _buffer, offset);
		tag = tag>>3;
	    switch(tag){
	        /* tag of: _Hello._counter */
	        case 1 :
	        	offset = read_raw_varint32(&tag, _buffer, offset);
	        	_Hello->_counter = tag;
	        	break;
	    }
	}
	
	return offset;
}

int Hello_read_delimited_from(void *_buffer, struct Hello *_Hello, int offset) {
	unsigned long size;
	
	offset = read_raw_varint32(&size, _buffer, offset);
	Hello_read(_buffer, _Hello, offset, size + offset);
	
	return offset + size;
}