



#include <allegro_flare/json.h>




namespace JSON
{




   // Value

   std::string Value::toString(void)
   {
      return value;
   }




   std::string Value::as_string(void)
   {
      JSON::String s = static_cast<JSON::String &>(*this);
      return s.stringValue();
   }




   Object Value::as_object(void)
   {
      std::string str = this->toString();
      JSON::Object o = static_cast<JSON::Object &>(JSON::decode(str));
      return o;
   }




   Array Value::as_array(void)
   {
      std::string str = this->toString();
      JSON::Array a = static_cast<JSON::Array &>(JSON::decode(str));
      return a;
   }




   int Value::as_integer(void)
   {
      JSON::Integer i = static_cast<JSON::Integer &>(*this);
      return i.intValue();
   }




   float Value::as_float(void)
   {
      JSON::Float f = static_cast<JSON::Float &>(*this);
      return f.floatValue();
   }




   bool Value::as_bool(void)
   {
      JSON::Boolean b = static_cast<JSON::Boolean &>(*this);
      return b.boolValue();
   }




   // Object

   std::string Object::toString(void)
   {
      value = "{";

      std::map<std::string, Value *>::const_iterator i = values.begin();
      if (i != values.end())
      {
         while (true)
         {
            // TODO: escape string
            value += '"' + i->first + "\":";				
            value += i->second->toString();
            ++i;
            if (i == values.end()) break;
            value += ",";
         }
      }	
      value += "}";

      return value;	
   }




   Value& Object::operator[](std::string const &key)
   {
      return *values[key];
   }




   bool Object::exists(std::string const &key)
   {
      return values.find(key) != values.end();
   }




   // Array

   void Array::push(Value *value)
   {
      values.push_back(value);
   }			




   std::string Array::toString(void)
   {
      value = "[";

      std::vector<Value *>::const_iterator i = values.begin();
      if (i != values.end())
      {
         while (true)
         {
            value += (*i)->toString();
            ++i;
            if (i == values.end()) break;
            value += ",";
         }
      }	
      value += "]";

      return value;	
   }




   Value &Array::operator[](size_t i) const
   {
      return *values[i];
   }




   // String

   std::string String::toString()
   {
      // TODO: string encode value
      return '"' + value + '"';
   }




   std::string String::stringValue() const
   {
      return value;
   }




   // Integer

   int Integer::intValue() const
   {
      return atoi(value.c_str());
   }




   // Float

   float Float::floatValue() const
   {
      return (float)atof(value.c_str());
   }




   // Boolean

   Boolean::Boolean(bool b)
   {
      value = b ? "true" : "false";
   }

   bool Boolean::boolValue() const
   {
      return value == "true" ? true : false;
   }




   // Null

   Null::Null()
   {
      value = "null";
   }




   // Parser

   void Parser::nextToken()
   {
      prev = current;
      current.type = Token::ENDOF;

      while (i < (int)json.length())
      {
         if (json[i] == ' ' || json[i] == '\t' || json[i] == '\n' || json[i] == '\r')
         {
            ++i;
         }
         else if (json[i] == '{')
         {
            current.type = Token::BRACE_OPEN;
            ++i;
            break;
         }
         else if (json[i] == '}')
         {
            current.type = Token::BRACE_CLOSE;
            ++i;
            break;
         }
         else if (json[i] == '[')
         {
            current.type = Token::BRACKET_OPEN;
            ++i;
            break;
         }
         else if (json[i] == ']')
         {
            current.type = Token::BRACKET_CLOSE;
            ++i;
            break;
         }
         else if (json[i] == ',')
         {
            current.type = Token::COMMA;
            ++i;
            break;
         }
         else if (json[i] == ':')
         {
            current.type = Token::COLON;
            ++i;
            break;
         }
         else if ((json[i] >= '0' && json[i] <= '9') || json[i] == '-')
         {
            std::string s;
            bool is_integer = true;
            int j = i;

            if (json[j] == '-')
            {
               s = '-';
               ++j;
               if (json[j] < '0' || json[j] > '9') throw "found -, expecting a number";
            }

            if (json[j] == '0')
            {
               s += '0';
               ++j;
            }
            else
            {
               ++j;
               while (j < (int)json.length() && json[j] >= '0' && json[j] <= '9')
               {
                  ++j;
               }					
            }

            if (j < (int)json.length()) // wrap check
            {
               if (json[j] == '.')
               {
                  bool got_digit = false;
                  is_integer = false;
                  ++j;
                  while (j < (int)json.length() && json[j] >= '0' && json[j] <= '9')
                  {
                     got_digit = true;
                     ++j;
                  }

                  if (!got_digit) throw "invalid decimal";
               }

               if (json[j] == 'e' || json[j] == 'E')
               {
                  is_integer = false;

                  ++j;
                  if (json[j] == '+' || json[j] == '-') ++j;

                  bool got_digit = false;

                  while (j < (int)json.length() && json[j] >= '0' && json[j] <= '9')
                  {
                     got_digit = true;
                     ++j;
                  }
                  if (!got_digit) throw "invalid exponent";
               }
            }

            current.type = is_integer ? Token::INTEGER : Token::FLOAT;
            current.value = json.substr(i, j-i);
            i = j;

            break;
         }
         else if (json[i] == '"')
         {
            std::string s;
            for (int j = i + 1; j < (int)json.length(); ++j)
            {
               if (json[j] == '\\')
               {
                  if (++j == json.length()) throw "invalid escape";

                  char c = json[j];
                  if (c == '"' || c == '/' || c == '\\')
                     s += c;
                  else if (c == 'b')
                     s += '\b';
                  else if (c == 'f')
                     s += '\f';
                  else if (c == 'n')
                     s += '\n';
                  else if (c == 'r')
                     s += '\r';
                  else if (c == 't')
                     s += '\t';
                  else if (c == 'u')
                     throw "unicode escape not supported";
                  else
                     throw "invalid escape sequence";
               }
               else if (json[j] == '"')
               {
                  current.type = Token::STRING;
                  current.value = s;
                  i = j + 1;
                  return;
               }
               else
                  s += json[j];
            }				
            throw "unterminated string";
         }
         else if (json[i] >= 'a' && json[i] <= 'z')
         {
            int j;
            for (j = i + 1; j < (int)json.length(); ++j)
            {
               if (!(
                        (json[j] >= 'a' && json[j] <= 'z') ||
                        (json[j] >= 'A' && json[j] <= 'Z') ||
                        (json[j] >= '0' && json[j] <= '9') ||
                        json[j] == '_'
                    )) break;
            }
            current.type = Token::KEYWORD;
            current.value = json.substr(i, j-i);
            i = j;
            return;
         }
         else
            throw "oops";
      }

   }




   Parser::Parser(const std::string &json) : json(json), i(0)
   {
   }




   bool Parser::accept(int type)
   {
      if (current.type == type)
      {
         nextToken();
         return true;
      }

      return false;
   }




   void Parser::expect(int type)
   {
      if (!accept(type))
         throw "expect: fail!";
   }




   Value *Parser::acceptArray()
   {
      if (accept(Token::BRACKET_OPEN))
      {
         Array *v = new Array();
         Value *c = acceptValue();
         if (c)
         {
            v->push(c);
            while (accept(Token::COMMA))
            {
               c = expectValue();
               v->push(c);
            }
         }
         expect(Token::BRACKET_CLOSE);

         return v;
      }

      return NULL;
   }




   Value *Parser::acceptObject()
   {
      if (accept(Token::BRACE_OPEN))
      {
         Object *v = new Object();

         if (current.type == Token::STRING)
         {
            do {
               expect(Token::STRING);
               std::string key = prev.value;
               expect(Token::COLON);
               Value *val = expectValue();

               v->values[key] = val;					
            } while (accept(Token::COMMA));
         }

         expect(Token::BRACE_CLOSE);

         return v;
      }

      return NULL;
   }




   Value *Parser::acceptInteger()
   {
      if (accept(Token::INTEGER))
      {
         Value *v = new Integer;
         v->value = prev.value;
         return v;
      }

      return NULL;
   }




   Value *Parser::acceptFloat()
   {
      if (accept(Token::FLOAT))
      {
         Value *v = new Float;
         v->value = prev.value;
         return v;
      }

      return NULL;
   }




   Value *Parser::acceptString()
   {
      if (accept(Token::STRING))
      {
         Value *v = new String;
         v->value = prev.value;
         return v;
      }

      return NULL;
   }




   Value *Parser::acceptNumber()
   {
      Value *v;
      if ((v = acceptInteger())) return v;
      if ((v = acceptFloat())) return v;

      return NULL;
   }




   Value *Parser::acceptBoolean()
   {
      if (current.type == Token::KEYWORD)
      {
         if (current.value == "true")
         {
            accept(Token::KEYWORD);
            return new Boolean(true);
         }
         else if (current.value == "false")
         {
            accept(Token::KEYWORD);
            return new Boolean(false);
         }
      }

      return NULL;
   }




   Value *Parser::acceptNull()
   {
      if (current.type == Token::KEYWORD && current.value == "null")
      {
         accept(Token::KEYWORD);
         return new Null();
      }
      return NULL;
   }




   Value *Parser::acceptValue()
   {
      Value *v;
      if ((v = acceptArray())) return v;
      if ((v = acceptBoolean())) return v;
      if ((v = acceptNull())) return v;
      if ((v = acceptNumber())) return v;
      if ((v = acceptObject())) return v;
      if ((v = acceptString())) return v;

      return NULL;
   }




   Value *Parser::expectValue()
   {
      Value *v = acceptValue();
      if (!v) throw "expected value";
      return v;
   }




   Value *Parser::parse()
   {
      Value *v;
      nextToken();
      v = acceptValue();
      if (!v) v = new Null;

      expect(Token::ENDOF);

      return v;
   }




   Value &decode(const std::string &json)
   {
      Parser p(json);
      return *p.parse();
   }
}




// added functions




JSON::Float json_float(std::string str)
{
	JSON::Float f = static_cast<JSON::Float &>(JSON::decode(str));
	return f;
}




JSON::String json_string(std::string str)
{
	JSON::String s = static_cast<JSON::String &>(JSON::decode(str));
	return s;
}




JSON::Integer json_int(std::string str)
{
	JSON::Integer i = static_cast<JSON::Integer &>(JSON::decode(str));
	return i;
}




JSON::Object json_object(std::string str)
{
	JSON::Object o = static_cast<JSON::Object &>(JSON::decode(str));
	return o;
}




JSON::Array json_array(std::string str)
{
	JSON::Array a = static_cast<JSON::Array &>(JSON::decode(str));
   return a;
}




JSON::Boolean json_bool(std::string str)
{
	return static_cast<JSON::Boolean &>(JSON::decode(str));
}




JSON::Null json_null(std::string str)
{
	return static_cast<JSON::Null &>(JSON::decode(str));
}




