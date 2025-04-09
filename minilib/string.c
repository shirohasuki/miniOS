#include "minilib.h"

size_t strnlen(const char *s, size_t count) {
	const char *sc;
	for (sc = s; count-- && *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}

size_t strlen(const char *s) {
  size_t count = 0; 
  for (; *s!='\0'; s++){
  count++;
  }
  return count;
}

char *strcpy(char *dst, const char *src) { 
  char *ret = dst;
  for (; *src!='\0'; src++,dst++){
  *dst = *src;
  }
  *dst = '\0';
  return ret;
}

char *strncpy(char *dst, const char *src, size_t n) {
  char *ret = dst;
  for (size_t i=0; i<n;i++){
  *(dst+i) = *(src+i);
  }
  *(dst+n) = '\0';
  return ret;
}

char *strcat(char *dst, const char *src) { 
  char *ret = dst;
  for (; *dst!='\0'; dst++); // dst -> '\0'
  strcpy(dst,src);
  return ret;
}

int strcmp(const char *s1, const char *s2) { 
  int ret = 0;
  for (; *s1 !='\0' && *s2!='\0' ; s1++,s2++){
  ret = *s1 - *s2;
  if (ret != 0)
    return ret; //can not be break!
  }
  ret = *s1 - *s2; //check for finish '\0'.
  return ret;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  int ret = 0;
  for (size_t i = 0; i < n ;i++){
  ret = *(s1+i) - *(s2+i);
  if (ret!=0)
    break;
  }
  return ret; 
}

void *memset(void *s, int c, size_t n) { 
  unsigned char *p = (unsigned char *)s;
  for (size_t i = 0; i < n; i++){
  *(p+i) = c;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  // this function can be uesd for overlapping areas.
  if (dst <= src) {
  // ----|dst----------|src---------|----------
  char *pdst = (char *) dst;
  char *psrc = (char *) src;
  for (size_t i = 0; i < n; i++){
    *pdst++ = *psrc++;
  }
  } 
  else {
  // ----|src----------|dst---------|----------
  char *pdst = (char *) dst + n;
  char *psrc = (char *) src + n;
  for (size_t i = 0; i < n; i++){
    *--pdst = *--psrc;
  }
  }
  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  // this function can not be uesd for overlapping areas!
  char *pout = (char *) out;
  const char *pin = (char *) in;
  for (size_t i = 0; i < n; i++){
  *pout++ = *pin++;
  }
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) { 
  int ret = 0;
  const unsigned char *p1 = s1;
  const unsigned char *p2 = s2;
  for (size_t i = 0; i < n; i++){
  ret = *(p1 + i) - *(p2 + i);
  if (ret != 0)
    break;
  }
  return ret; 
}

static char *save_ptr;

char *strtok(char *str, const char *delim) {
  char *token_start;
  
  // 如果str为NULL，则继续处理上次的字符串
  if (!str) {
    str = save_ptr;
  }
  
  // 跳过开头的分隔符
  while (*str && strchr(delim, *str)) {
    str++;
  }
  
  // 如果到达字符串末尾，返回NULL
  if (!*str) {
    save_ptr = str;
    return NULL;
  }
  
  // 找到token的开始位置
  token_start = str;
  
  // 找到下一个分隔符
  while (*str && !strchr(delim, *str)) {
    str++;
  }
  
  if (*str) {
    *str = '\0';  // 在分隔符位置放置字符串结束符
    save_ptr = str + 1;
  } else {
    save_ptr = str;  // 指向字符串末尾
  }
  
  return token_start;
}

char *strchr(const char *s, int c) {
  while (*s != '\0') {
    if (*s == (char)c) {
      return (char *)s;
    }
    s++;
  }
  return NULL;
}
