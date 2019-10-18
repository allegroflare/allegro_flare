#ifndef __AF_JSON_HEADER
#define __AF_JSON_HEADER




#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>




namespace allegro_flare
{
   namespace JSON
   {
      class Array;
      class Object;

      class Value
      {
      public:
         Value();
         virtual ~Value();

         std::string value;
         virtual std::string toString(void);

         std::string as_string();
         JSON::Object as_object();
         JSON::Array as_array();
         int as_integer();
         float as_float();
         bool as_bool();
      };

      class Object : public Value
      {
      public:
         Object();
         virtual ~Object();

         std::map<std::string, Value *> values;

         virtual std::string toString(void);

         Value& operator[](std::string const &key);
         bool exists(std::string const &key);
      };

      class Array : public Value
      {
      public:
         Array();
         virtual ~Array();

         std::vector<Value *> values;
         void push(Value *value);

         virtual std::string toString(void);
         Value &operator[](size_t i) const;
      };

      class String : public Value
      {
      public:
         String();
         virtual ~String();

         virtual std::string toString(void);
         std::string stringValue() const;
      };

      class Integer : public Value
      {
      public :
         int intValue() const;
      };

      class Float : public Value
      {
      public:
         float floatValue() const;
      };

      class Boolean : public Value
      {
      public:
         Boolean(bool b);
         bool boolValue() const;
      };

      class Null : public Value
      {
      public:
         Null();
      };

      /* private */
      class Token
      {
      public:
         enum {
            ENDOF = 0,
            INTEGER,
            FLOAT,
            STRING,
            COMMA,
            KEYWORD,
            COLON,
            BRACE_OPEN,
            BRACE_CLOSE,
            BRACKET_OPEN,
            BRACKET_CLOSE
         } type;
         std::string value;
      };

      class Parser
      {
      private:
         std::string json;
         int i;
         Token current, prev;

         void nextToken();

      public:
         Parser(const std::string &json);

         bool accept(int type);
         void expect(int type);

         Value *acceptArray();
         Value *acceptObject();
         Value *acceptInteger();
         Value *acceptFloat();
         Value *acceptString();
         Value *acceptNumber();
         Value *acceptBoolean();
         Value *acceptNull();
         Value *acceptValue();
         Value *expectValue();
         Value *parse();
      };

      Value &decode(const std::string &json);
   }




   JSON::String json_string(std::string str);

   JSON::Integer json_int(std::string str);

   JSON::Float json_float(std::string str);

   JSON::Boolean json_bool(std::string str);

   JSON::Array json_array(std::string str);

   JSON::Object json_object(std::string str);

   JSON::Null json_null(std::string str);
}




#endif
