

#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/Script.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::Script script;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest, get_current_line_text__gets_the_text_from_the_current_line)
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


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest, at_last_line__returns_true_if_on_the_last_line)
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


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest, at_last_line__returns_false_if_not_on_the_last_line)
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


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest,
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


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest, goto_next_line__will_advance_the_current_line_num__and_return_true)
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


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest, goto_next_line__if_currently_at_the_last_line__returns_true)
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


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest, goto_next_line__with_no_lines_returns_false)
{
   AllegroFlare::Prototypes::FixedRoom2D::Script script;
   script.initialize();

   ASSERT_EQ(false, script.goto_next_line());
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest,
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


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest,
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


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest,
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


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest, goto_marker__if_the_marker_does_not_exist__returns_false)
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


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest, goto_line_num__sets_the_current_line_num_and_returns_true)
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


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest, goto_line_num__works_for_the_whole_range_of_valid_line_numbers)
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


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest,
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


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest,
   build_markers_index__will_build_an_index_with_the_markers_and_line_numbers_from_the_script)
{
   std::vector<std::string> lines = {
      { "MARKER: *MY_START_MARKER*" },
      { "This is the first line of the script." },
      { "This is the second line of the script." },
      { "If you've made it this far, you might have a chance." },
      { "In fact, I'll even give you a choice." },
      { "Or at least, the illusion of one ;)" },
      { "CHOICE: Where would you like to go? | Back to the top | GOTO *MY_START_MARKER* | "
           "Take me to the end | GOTO *MY_END_MARKER*" },
      { "MARKER: *MY_END_MARKER*" },
      { "Look at this kid. He might have a shot after all." },
   };

   std::map<std::string, int> built_index = AllegroFlare::Prototypes::FixedRoom2D::Script::build_markers_index(lines);

   std::map<std::string, int> expected_index = { { "*MY_START_MARKER*", 1 }, { "*MY_END_MARKER*", 8 } };
   ASSERT_EQ(expected_index, built_index);
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest,
   build_markers_index__will_include_markers_at_the_beginning_and_the_end)
{
   std::vector<std::string> lines = {
      { "MARKER: *A_MARKER_AT_THE_FIRST_LINE*" },
      { "This is just a line in the middle." },
      { "MARKER: *A_MARKER_AT_THE_LAST_LINE*" },
   };

   std::map<std::string, int> built_index = AllegroFlare::Prototypes::FixedRoom2D::Script::build_markers_index(lines);

   std::map<std::string, int> expected_index = {
      { "*A_MARKER_AT_THE_FIRST_LINE*", 1 },
      { "*A_MARKER_AT_THE_LAST_LINE*", 3 },
   };
   ASSERT_EQ(expected_index, built_index);
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest,
   build_markers_index__if_a_script_has_multiple_identical_markers__will_generate_a_warning)
{
   std::vector<std::string> lines = {
      { "MARKER: *A_MARKER_THAT_EXISTS_IN_TWO_PLACES*" },
      { "This is just a line in the middle." },
      { "MARKER: *A_MARKER_THAT_EXISTS_IN_TWO_PLACES*" },
   };

   testing::internal::CaptureStdout();
   std::map<std::string, int> built_index = AllegroFlare::Prototypes::FixedRoom2D::Script::build_markers_index(lines);
   std::string cout_output = testing::internal::GetCapturedStdout();

   std::string expected_warning_message = "FixedRoom2D::Script::build_markers_index: WARNING: "
      "the marker \"*A_MARKER_THAT_EXISTS_IN_TWO_PLACES*\"is being set on line 3 but was already declared earlier "
      "on line 1. Note that the marker will be overwritten to this new line number (3).";

   ASSERT_EQ(expected_warning_message, cout_output);
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptTest,
   build_markers_index__if_a_script_has_multiple_identical_markers__will_set_the_line_number_to_the_last_declaration)
{
   std::vector<std::string> lines = {
      { "MARKER: *A_MARKER_THAT_EXISTS_IN_TWO_PLACES*" },
      { "This is just a line in the middle." },
      { "MARKER: *A_MARKER_THAT_EXISTS_IN_TWO_PLACES*" },
   };

   std::map<std::string, int> built_index = AllegroFlare::Prototypes::FixedRoom2D::Script::build_markers_index(lines);

   std::map<std::string, int> expected_index = {
      { "*A_MARKER_THAT_EXISTS_IN_TWO_PLACES*", 3 },
   };
   ASSERT_EQ(expected_index, built_index);
}


