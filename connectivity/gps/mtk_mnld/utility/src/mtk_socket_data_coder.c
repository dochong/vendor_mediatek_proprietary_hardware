// This source code is generated by UdpGeneratorTool, not recommend to modify it directly
#include "mtk_socket_data_coder.h"

bool mtk_socket_get_bool(char* buff, int* offset) {
    bool ret = (mtk_socket_get_char(buff, offset) == 0)? false : true;
    return ret;
}

char mtk_socket_get_char(char* buff, int* offset) {
    char ret = buff[*offset];
    *offset += 1;
    return ret;
}

short mtk_socket_get_short(char* buff, int* offset) {
    short ret = 0;
    ret |= mtk_socket_get_char(buff, offset) & 0xff;
    ret |= (mtk_socket_get_char(buff, offset) << 8);
    return ret;
}

int mtk_socket_get_int(char* buff, int* offset) {
    int ret = 0;
    ret |= mtk_socket_get_short(buff, offset) & 0xffff;
    ret |= (mtk_socket_get_short(buff, offset) << 16);
    return ret;
}

int64_t mtk_socket_get_int64_t(char* buff, int* offset) {
    int64_t ret = 0;
    ret |= mtk_socket_get_int(buff, offset) & 0xffffffffL;
    ret |= ((int64_t)mtk_socket_get_int(buff, offset) << 32);
    return ret;
}

float mtk_socket_get_float(char* buff, int* offset) {
    float ret;
    int tmp = mtk_socket_get_int(buff, offset);
    ret = *((float*)&tmp);
    return ret;
}

double mtk_socket_get_double(char* buff, int* offset) {
    double ret;
    int64_t tmp = mtk_socket_get_int64_t(buff, offset);
    ret = *((double*)&tmp);
    return ret;
}

int mtk_socket_get_string(char* buff, int* offset, char* output, int max_size) {
    int size = mtk_socket_get_int(buff, offset);
    memset(output, 0, max_size);
    memcpy(output, &buff[*offset], (size > max_size)? max_size : size);
    output[max_size - 1] = 0;
    *offset += size;
    return (size > max_size)? max_size : size;
}

int mtk_socket_get_bool_array(char* buff, int* offset, bool output[], int max_size) {
    int i = 0;
    int size = mtk_socket_get_int(buff, offset);
    for(i = 0; i < size; i++) {
        bool data = mtk_socket_get_bool(buff, offset);
        if(i < max_size) {
            output[i] = data;
        }
    }
    return (size > max_size)? max_size : size;
}

int mtk_socket_get_char_array(char* buff, int* offset, char output[], int max_size) {
    int size = mtk_socket_get_int(buff, offset);
    memcpy(output, &buff[*offset], (size > max_size)? max_size : size);
    *offset += size;
    return (size > max_size)? max_size : size;
}

int mtk_socket_get_short_array(char* buff, int* offset, short output[], int max_size) {
    int i = 0;
    int size = mtk_socket_get_int(buff, offset);
    for(i = 0; i < size; i++) {
        short data = mtk_socket_get_short(buff, offset);
        if(i < max_size) {
            output[i] = data;
        }
    }
    return (size > max_size)? max_size : size;
}

int mtk_socket_get_int_array(char* buff, int* offset, int output[], int max_size) {
    int i = 0;
    int size = mtk_socket_get_int(buff, offset);
    for(i = 0; i < size; i++) {
        int data = mtk_socket_get_int(buff, offset);
        if(i < max_size) {
            output[i] = data;
        }
    }
    return (size > max_size)? max_size : size;
}

int mtk_socket_get_int64_t_array(char* buff, int* offset, int64_t output[], int max_size) {
    int i = 0;
    int size = mtk_socket_get_int(buff, offset);
    for(i = 0; i < size; i++) {
        int64_t data = mtk_socket_get_int64_t(buff, offset);
        if(i < max_size) {
            output[i] = data;
        }
    }
    return (size > max_size)? max_size : size;
}

int mtk_socket_get_float_array(char* buff, int* offset, float output[], int max_size) {
    int i = 0;
    int size = mtk_socket_get_int(buff, offset);
    for(i = 0; i < size; i++) {
        float data = mtk_socket_get_float(buff, offset);
        if(i < max_size) {
            output[i] = data;
        }
    }
    return (size > max_size)? max_size : size;
}

int mtk_socket_get_double_array(char* buff, int* offset, double output[], int max_size) {
    int i = 0;
    int size = mtk_socket_get_int(buff, offset);
    for(i = 0; i < size; i++) {
        double data = mtk_socket_get_double(buff, offset);
        if(i < max_size) {
            output[i] = data;
        }
    }
    return (size > max_size)? max_size : size;
}

int mtk_socket_get_string_array(char* buff, int* offset, void* output, int max_size1, int max_size2) {
    int i = 0;
    int size1 = mtk_socket_get_int(buff, offset);
    for(i = 0; i < size1; i++) {
        if(i < max_size1) {
            mtk_socket_get_string(buff, offset, output, max_size2);
            output = (char*)output + max_size2;
        } else {
            char tmp[max_size2];
            mtk_socket_get_string(buff, offset, tmp, max_size2);
        }
    }
    return (size1 > max_size1)? max_size1 : size1;
}

void mtk_socket_put_bool(char* buff, int* offset, bool input) {
    mtk_socket_put_char(buff, offset, input);
}

void mtk_socket_put_char(char* buff, int* offset, char input) {
    *((char*)&buff[*offset]) = input;
    *offset += 1;
}

void mtk_socket_put_short(char* buff, int* offset, short input) {
    mtk_socket_put_char(buff, offset, input & 0xff);
    mtk_socket_put_char(buff, offset, (input >> 8) & 0xff);
}

void mtk_socket_put_int(char* buff, int* offset, int input) {
    mtk_socket_put_short(buff, offset, input & 0xffff);
    mtk_socket_put_short(buff, offset, (input >> 16) & 0xffff);
}

void mtk_socket_put_int64_t(char* buff, int* offset, int64_t input) {
    mtk_socket_put_int(buff, offset, input & 0xffffffffL);
    mtk_socket_put_int(buff, offset, ((input >> 32L) & 0xffffffffL));
}

void mtk_socket_put_float(char* buff, int* offset, float input) {
    int* data = (int*)&input;
    mtk_socket_put_int(buff, offset, *data);
}

void mtk_socket_put_double(char* buff, int* offset, double input) {
    int64_t* data = (int64_t*)&input;
    mtk_socket_put_int64_t(buff, offset, *data);
}

void mtk_socket_put_string(char* buff, int* offset, const char* input) {
    int len = strlen(input);
    mtk_socket_put_int(buff, offset, len);
    memcpy(&buff[*offset], input, len);
    *offset += len;
}

void mtk_socket_put_bool_array(char* buff, int* offset, bool input[], int size) {
    int i = 0;
    mtk_socket_put_int(buff, offset, size);
    for(i = 0; i < size; i++) {
        mtk_socket_put_bool(buff, offset, input[i]);
    }
}

void mtk_socket_put_char_array(char* buff, int* offset, char input[], int size) {
    mtk_socket_put_int(buff, offset, size);
    memcpy(&buff[*offset], input, size);
    *offset += size;
}

void mtk_socket_put_short_array(char* buff, int* offset, short input[], int size) {
    int i = 0;
    mtk_socket_put_int(buff, offset, size);
    for(i = 0; i < size; i++) {
        mtk_socket_put_short(buff, offset, input[i]);
    }
}

void mtk_socket_put_int_array(char* buff, int* offset, int input[], int size) {
    int i = 0;
    mtk_socket_put_int(buff, offset, size);
    for(i = 0; i < size; i++) {
        mtk_socket_put_int(buff, offset, input[i]);
    }
}

void mtk_socket_put_int64_t_array(char* buff, int* offset, int64_t input[], int size) {
    int i = 0;
    mtk_socket_put_int(buff, offset, size);
    for(i = 0; i < size; i++) {
        mtk_socket_put_int64_t(buff, offset, input[i]);
    }
}

void mtk_socket_put_float_array(char* buff, int* offset, float input[], int size) {
    int i = 0;
    mtk_socket_put_int(buff, offset, size);
    for(i = 0; i < size; i++) {
        mtk_socket_put_float(buff, offset, input[i]);
    }
}

void mtk_socket_put_double_array(char* buff, int* offset, double input[], int size) {
    int i = 0;
    mtk_socket_put_int(buff, offset, size);
    for(i = 0; i < size; i++) {
        mtk_socket_put_double(buff, offset, input[i]);
    }
}

void mtk_socket_put_string_array(char* buff, int* offset, void* input, int size1, int size2) {
    int i = 0;
    mtk_socket_put_int(buff, offset, size1);
    for(i = 0; i < size1; i++) {
        mtk_socket_put_string(buff, offset, (char*)input);
        input = (char*)input + size2;
    }
}

