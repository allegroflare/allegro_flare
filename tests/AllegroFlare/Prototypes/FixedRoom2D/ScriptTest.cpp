

#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/Script.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::Script script;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptText, get_current_line_text__gets_the_text_from_the_current_line)
{
   std::vector<std::string> script_lines = {
      "This is line 1.",
      "And another line making this one line 2.",
      "Lastly, a third line.",
   };
   AllegroFlare::Prototypes::FixedRoom2D::Script script(script_lines);
   script.initialize();

   ASSERT_EQ("This is line 1.", script.get_current_line_text());
   script.goto_line_num(2);
   ASSERT_EQ("And another line making this one line 2.", script.get_current_line_text());
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptText, at_last_line__returns_true_if_on_the_last_line)
{
   std::vector<std::string> script_lines = {
      "This is line 1.",
      "And another line making this one line 2.",
      "Lastly, a third line.",
   };
   AllegroFlare::Prototypes::FixedRoom2D::Script script(script_lines);
   script.initialize();

   script.goto_next_line();
   script.goto_next_line();
   ASSERT_EQ(true, script.at_last_line());
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptText, at_last_line__returns_false_if_not_on_the_last_line)
{
   std::vector<std::string> script_lines = {
      "This is line 1.",
      "And another line making this one line 2.",
      "Lastly, a third line.",
   };
   AllegroFlare::Prototypes::FixedRoom2D::Script script(script_lines);
   script.initialize();

   ASSERT_EQ(false, script.at_last_line());
   script.goto_next_line();
   ASSERT_EQ(false, script.at_last_line());
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptText,
   initialize__will_number_lines_such_that_the_first_line_is_line_number_1)
{
   std::vector<std::string> script_lines = {
      "This is line 1.",
      "And another line making this one line 2.",
      "Lastly, a third line.",
   };
   AllegroFlare::Prototypes::FixedRoom2D::Script script(script_lines);
   script.initialize();

   ASSERT_EQ(1, script.get_current_line_num());
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptText, goto_next_line__will_advance_the_current_line_num__and_return_true)
{
   std::vector<std::string> script_lines = {
      "This is line 1.",
      "And another line making this one line 2.",
      "Lastly, a third line.",
   };
   AllegroFlare::Prototypes::FixedRoom2D::Script script(script_lines);
   script.initialize();

   ASSERT_EQ(true, script.goto_next_line());
   ASSERT_EQ(2, script.get_current_line_num());
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptText, goto_next_line__if_currently_at_the_last_line__returns_true)
{
   std::vector<std::string> script_lines = {
      "This is line 1.",
      "And another line making this one line 2.",
      "Lastly, a third line.",
   };
   AllegroFlare::Prototypes::FixedRoom2D::Script script(script_lines);
   script.initialize();

   int last_line_num = script_lines.size();
   script.goto_line_num(last_line_num);

   ASSERT_EQ(true, script.goto_next_line());
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptText, goto_next_line__with_no_lines_returns_false)
{
   AllegroFlare::Prototypes::FixedRoom2D::Script script;
   script.initialize();

   ASSERT_EQ(false, script.goto_next_line());
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptText,
   goto_next_line__if_currently_at_the_last_line__sets_the_current_line_num_to_negative_1)
{
   std::vector<std::string> script_lines = {
      "This is line 1.",
      "And another line making this one line 2.",
      "Lastly, a third line.",
   };
   AllegroFlare::Prototypes::FixedRoom2D::Script script(script_lines);
   script.initialize();

   int last_line_num = script_lines.size();
   script.goto_line_num(last_line_num);

   ASSERT_EQ(true, script.goto_next_line());
   ASSERT_EQ(-1, script.get_current_line_num());
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptText,
   goto_next_line__if_currently_at_the_last_line__sets_finished_to_true)
{
   std::vector<std::string> script_lines = {
      "This is line 1.",
      "And another line making this one line 2.",
      "Lastly, a third line.",
   };
   AllegroFlare::Prototypes::FixedRoom2D::Script script(script_lines);
   script.initialize();

   int last_line_num = script_lines.size();
   script.goto_line_num(last_line_num);

   script.goto_next_line();
   ASSERT_EQ(true, script.get_finished());
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptText,
   goto_marker__sets_the_current_line_num_to_the_position_of_the_marker_and_returns_true)
{
   std::vector<std::string> script_lines = {
      "This is line 1.",
      "MARKER: *A*",
      "Lastly, a third line.",
   };
   AllegroFlare::Prototypes::FixedRoom2D::Script script(script_lines);
   script.initialize();

   EXPECT_EQ(true, script.goto_marker("*A*"));
   EXPECT_EQ(2, script.get_current_line_num());
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptText, goto_marker__if_the_marker_does_not_exist__returns_false)
{
   std::vector<std::string> script_lines = {
      "This is line 1.",
      "MARKER: *A*",
      "Lastly, a third line.",
   };
   AllegroFlare::Prototypes::FixedRoom2D::Script script(script_lines);
   script.initialize();

   EXPECT_EQ(false, script.goto_marker("*A_MARKER_THAT_DOES_NOT_EXIST*"));
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptText, goto_line_num__sets_the_current_line_num_and_returns_true)
{
   std::vector<std::string> script_lines = {
      "This is line 1.",
      "And another line making this one line 2.",
      "Lastly, a third line.",
   };
   AllegroFlare::Prototypes::FixedRoom2D::Script script(script_lines);
   script.initialize();

   ASSERT_EQ(true, script.goto_line_num(2));
   ASSERT_EQ(2, script.get_current_line_num());
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptText, goto_line_num__works_for_the_whole_range_of_valid_line_numbers)
{
   std::vector<std::string> script_lines = {
      "This is line 1.",
      "And another line making this one line 2.",
      "Lastly, a third line.",
   };
   AllegroFlare::Prototypes::FixedRoom2D::Script script(script_lines);
   script.initialize();

   for (unsigned i=0; i<script_lines.size(); i++)
   {
      int line_num_to_go_to = i+1;
      ASSERT_EQ(true, script.goto_line_num(line_num_to_go_to));
      ASSERT_EQ(line_num_to_go_to, script.get_current_line_num());
   }
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptText,
   goto_line_num__if_outside_the_range_of_lines__does_not_set_the_line_num__and_returns_false)
{
   std::vector<std::string> script_lines = {
      "This is line 1.",
      "And another line making this one line 2.",
      "Lastly, a third line.",
   };
   AllegroFlare::Prototypes::FixedRoom2D::Script script(script_lines);
   script.initialize();

   script.goto_line_num(2);

   ASSERT_EQ(false, script.goto_line_num(-1));
   ASSERT_EQ(2, script.get_current_line_num());
   ASSERT_EQ(false, script.goto_line_num(0));
   ASSERT_EQ(2, script.get_current_line_num());
   ASSERT_EQ(false, script.goto_line_num(-1));
   ASSERT_EQ(2, script.get_current_line_num());
   ASSERT_EQ(false, script.goto_line_num(4));
   ASSERT_EQ(2, script.get_current_line_num());
   ASSERT_EQ(false, script.goto_line_num(999));
   ASSERT_EQ(2, script.get_current_line_num());
}


