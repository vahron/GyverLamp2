// TODO
// защита от переполнения

char* mUtoa(uint32_t value, char *buffer, bool clear = 1);
char* mLtoa(int32_t value, char *buffer, bool clear = 1);
char* mFtoa(double value, int8_t decimals, char *buffer);

char* mUtoa(uint32_t value, char *buffer, bool clear) {
  buffer += 11;
  if (clear) *--buffer = 0;
  do {
    *--buffer = value % 10 + '0';
    value /= 10;
  } while (value != 0);
  return buffer;
}

char* mLtoa(int32_t value, char *buffer, bool clear) {
  bool minus = value < 0;
  if (minus) value = -value;
  buffer = mUtoa(value, buffer, clear);
  if (minus) *--buffer = '-';
  return buffer;
}

char* mFtoa(double value, int8_t decimals, char *buffer) {
  int32_t mant = (int32_t)value;
  value -= mant;
  uint32_t exp = 1;
  while (decimals--) exp *= 10;
  exp *= (float)value;
  /*buffer += 9;
    buffer = mUtoa(exp, buffer);
    --buffer = '.';
    buffer -= 11;
    buffer = mLtoa(mant, buffer, 0);*/
  buffer = ltoa(mant, buffer, DEC);
  byte len = strlen(buffer);
  *(buffer + len++) = '.';
  ltoa(exp, buffer + len++, DEC);
  return buffer;
}

class mString {
  public:
    int size = 0;
    char* buf;
    // system*this = buf;
    uint16_t length() {
      return strlen(buf);
    }
    void clear() {
      buf[0] = 0;
    }

    // constructor
    mString(char* buffer, int newSize) {
      //*this = buf;
      buf = buffer;
      size = newSize;
    }
    /*mString (const char c) {
    	init();
    	add(c);
      }
      mString (const char* data) {
    	init();
    	add(data);
      }
      mString (const __FlashStringHelper *data) {
    	init();
    	add(data);
      }
      mString (uint32_t value) {
    	init();
    	add(value);
      }
      mString (int32_t value) {
    	init();
    	add(value);
      }
      mString (uint16_t value) {
    	init();
    	add(value);
      }
      mString (int16_t value) {
    	init();
    	add(value);
      }
      mString (uint8_t value) {
    	init();
    	add(value);
      }
      mString (int8_t value) {
    	init();
    	add(value);
      }
      mString (double value, byte dec = 2) {
    	init();
    	add(value, dec);
      }*/

    // add
    mString& add(const char c) {
      byte len = length();
      buf[len++] = c;
      buf[len++] = 0;
      return *this;
    }
    mString& add(const char* data) {
      /*byte len = length();
        do {
        buf[len] = *(data++);
        } while (buf[len++] != 0);*/
      strcpy(buf + length(), data);
      return *this;
    }
    mString& add(const __FlashStringHelper *data) {
      PGM_P p = reinterpret_cast<PGM_P>(data);
      strcpy_P(buf + length(), p);
      return *this;
      /*do {
        buf[len] = (char)pgm_read_byte_near(p++);
        } while (buf[len++] != 0);
      */
    }
    mString& add(uint32_t value) {
      //char buf[11];
      //return add(mUtoa(value, buf));
      utoa(value, buf + length(), DEC);
      return *this;
    }
    mString& add(uint16_t value) {
      return add((uint32_t)value);
    }
    mString& add(uint8_t value) {
      return add((uint32_t)value);
    }
    mString& add(int32_t value) {
      //char buf[11];
      //return add(mLtoa(value, buf));
      ltoa(value, buf + length(), DEC);
      return *this;
    }
    mString& add(int16_t value) {
      return add((int32_t)value);
    }
    mString& add(int8_t value) {
      return add((int32_t)value);
    }
    mString& add(double value, int8_t dec = 2) {
      char buf[20];
      return add(mFtoa(value, dec, buf));
      //dtostrf(value, dec, DEC, buf+length());
      //return *this;
    }

    // add +=
    mString& operator += (const char c) {
      return add(c);
    }
    mString& operator += (const char* data) {
      return add(data);
    }
    mString& operator += (const __FlashStringHelper *data) {
      return add(data);
    }
    mString& operator += (uint32_t value) {
      return add(value);
    }
    mString& operator += (int32_t value) {
      return add(value);
    }
    mString& operator += (uint16_t value) {
      return add(value);
    }
    mString& operator += (int16_t value) {
      return add(value);
    }
    mString& operator += (uint8_t value) {
      return add(value);
    }
    mString& operator += (int8_t value) {
      return add(value);
    }
    mString& operator += (double value) {
      return add(value);
    }

    // assign
    mString& operator = (const char c) {
      clear();
      return add(c);
    }
    mString& operator = (const char* data) {
      clear();
      return add(data);
    }
    mString& operator = (const __FlashStringHelper *data) {
      clear();
      return add(data);
    }
    mString& operator = (uint32_t value) {
      clear();
      return add(value);
    }
    mString& operator = (int32_t value) {
      clear();
      return add(value);
    }
    mString& operator = (uint16_t value) {
      clear();
      return add(value);
    }
    mString& operator = (int16_t value) {
      clear();
      return add(value);
    }
    mString& operator = (uint8_t value) {
      clear();
      return add(value);
    }
    mString& operator = (int8_t value) {
      clear();
      return add(value);
    }
    mString& operator = (double value) {
      clear();
      return add(value);
    }

    // compare
    bool operator == (const char c) {
      return (buf[0] == c && buf[1] == 0);
    }
    bool operator == (const char* data) {
      return !strcmp(buf, data);
    }
    bool operator == (uint32_t value) {
      char valBuf[11];
      return !strcmp(buf, utoa(value, valBuf, DEC));
    }
    bool operator == (int32_t value) {
      char valBuf[11];
      return !strcmp(buf, ltoa(value, valBuf, DEC));
    }
    bool operator == (float value) {
      char valBuf[20];
      return !strcmp(buf, mFtoa(value, 2, valBuf));
    }
    char operator [] (uint16_t index) const {
      return (index < size ? buf[index] : 0);
    }
    char& operator [] (uint16_t index) {
      return buf[index];
    }


    // convert & parse
    uint32_t toInt() {
      return atoi(buf);
    }
    float toFloat() {
      return atof(buf);
    }
    const char* c_str() {
      return buf;
    }
    bool startsWith(const char *data) {
      return strlen(data) == strspn(buf, data);
    }

    int indexOf(char ch, uint16_t fromIndex = 0) {
      if (fromIndex >= length()) return -1;
      const char* temp = strchr(buf + fromIndex, ch);
      if (temp == NULL) return -1;
      return temp - buf;
    }
    int parseBytes(byte* data, int len, char div = ',', char ter = NULL) {
      int b = 0, c = 0;
      data[b] = 0;
      while (true) {
        if (buf[c] == div) {
          b++;
          c++;
          if (b == len) return b;
          data[b] = 0;
          continue;
        }
        if (buf[c] == ter || b == len) return b + 1;
        data[b] *= 10;
        data[b] += buf[c] - '0';
        c++;
      }
    }
    int parseInts(int* data, int len, char div = ',', char ter = NULL) {
      int b = 0, c = 0;
      data[b] = 0;
      while (true) {
        if (buf[c] == div) {
          b++;
          c++;
          if (b == len) return b;
          data[b] = 0;
          continue;
        }
        if (buf[c] == ter || b == len) return b + 1;
        data[b] *= 10;
        data[b] += buf[c] - '0';
        c++;
      }
    }
  private:

};
