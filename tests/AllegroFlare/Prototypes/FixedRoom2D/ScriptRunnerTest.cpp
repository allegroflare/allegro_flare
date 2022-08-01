
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptRunner.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner script_runner;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest,
   load_current_script_lines__will_set_the_current_script_lines)
{
   // TODO
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest,
   parse_command_and_argument__will_not_blow_up_on_an_empty_line)
   // note this is a private method test
{
   std::string script_line = "";
   std::pair<std::string, std::string> parsed_command_argument_pair;
   AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner script_loader;

   parsed_command_argument_pair = script_loader.parse_command_and_argument(script_line);

   std::pair<std::string, std::string> expected_command_argument_pair = {"", ""};

   EXPECT_EQ(expected_command_argument_pair, parsed_command_argument_pair);
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest,
   parse_command_and_argument__will_parse_a_script_line_into_an_expected_set_of_elements)
   // note this is a private method test
{
   std::string script_line = "DIALOG: This is the most basic dialog.";
   std::pair<std::string, std::string> parsed_command_argument_pair;
   AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner script_loader;

   parsed_command_argument_pair = script_loader.parse_command_and_argument(script_line);

   std::pair<std::string, std::string> expected_command_argument_pair = {"DIALOG", "This is the most basic dialog."};

   EXPECT_EQ(expected_command_argument_pair, parsed_command_argument_pair);
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest,
   parse_command_and_argument__on_a_line_with_no_command__will_parse_to_a_DIALOG_and_trim_the_text)
   // note this is a private method test
{
   std::string script_line = "  \tThis line will not include a command, and will be trimmed. \n ";
   std::pair<std::string, std::string> parsed_command_argument_pair;
   AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner script_loader;

   parsed_command_argument_pair = script_loader.parse_command_and_argument(script_line);

   std::pair<std::string, std::string> expected_command_argument_pair = {
      "",
      "This line will not include a command, and will be trimmed."
   };

   EXPECT_EQ(expected_command_argument_pair, parsed_command_argument_pair);
}


//TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest, parse_and_run_line__will_parse_a_DIALOG_command)
   //// note this is a private method test
//{
   //std::string script_line = "DIALOG: This is the most basic dialog line.";
   //AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner script_loader;

   //script_loader.parse_and_run_line(script_line);
   //Krampus21::DialogBoxes::Base* created_dialog = script_loader.get_current_dialog();

   //ASSERT_NE(nullptr, created_dialog);
   //EXPECT_EQ("Basic", created_dialog->get_type());
//}


//TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest, parse_and_run_line__will_parse_a_CHOICE_command)
   //// note this is a private method test
//{
   //std::string script_line = "CHOICE: What would you choose? | Apple | COLLECT: APPLE | Pear | COLLECT: PEAR";
   //AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner script_loader;

   //script_loader.parse_and_run_line(script_line);
   //Krampus21::DialogBoxes::Base* created_dialog = script_loader.get_current_dialog();

   //ASSERT_NE(nullptr, created_dialog);
   //ASSERT_EQ("Choice", created_dialog->get_type());

   //Krampus21::DialogBoxes::Choice* created_choice_dialog = static_cast<Krampus21::DialogBoxes::Choice*>(created_dialog);

   //std::string expected_prompt = "What would you choose?";
   //std::vector<std::pair<std::string, std::string>> expected_options = {
      //{ "Apple", "COLLECT: APPLE" },
      //{ "Pear", "COLLECT: PEAR" },
   //};
   //EXPECT_EQ(expected_prompt, created_choice_dialog->get_prompt());
   //EXPECT_EQ(expected_options, created_choice_dialog->get_options());
   //delete created_dialog;
//}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest, parse__command_and_argument__will_trim_the_argument_fragment)
   // note this is a private method test
{
   std::string script_line = "  DIALOG  :  This is the most basic dialog that should be trimmed  \n  ";
   std::pair<std::string, std::string> parsed_command_argument_pair;
   AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner script_loader;

   parsed_command_argument_pair = script_loader.parse_command_and_argument(script_line);

   std::pair<std::string, std::string> expected_command_argument_pair = {
      "DIALOG",
      "This is the most basic dialog that should be trimmed",
   };

   EXPECT_EQ(expected_command_argument_pair, parsed_command_argument_pair);
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest, tokenize__will_split_a_source_string_into_trimmed_tokens)
   // note this is a private method test
{
   std::string source_string = "  Voo| do |daah || \t dang ";
   std::vector<std::string> expected_tokens = { "Voo", "do", "daah", "", "dang" };
   std::vector<std::string> actual_tokens = AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::tokenize(source_string);
   EXPECT_EQ(expected_tokens, actual_tokens);
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest, assert_min_token_count__will_return_true_if_there_are_at_least_n_tokens)
{
   ASSERT_EQ(true, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_min_token_count({}, 0));
   ASSERT_EQ(true, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_min_token_count({ "t1", "t2", "t3" }, 3));
   ASSERT_EQ(true, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_min_token_count({ "t1", "t2", "t3", "t4" }, 2));
}

TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest, assert_min_token_count__will_return_false_if_there_are_less_than_n_tokens)
{
   ASSERT_EQ(false, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_min_token_count({}, 1));
   ASSERT_EQ(false, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_min_token_count({ "t1", "t2", "t3" }, 4));
   ASSERT_EQ(false, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_min_token_count({ "t1", "t2", "t3", "t4" }, 999));
}

TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest, assert_odd_token_count__will_return_true_if_the_number_of_tokens_is_odd)
{
   ASSERT_EQ(true, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_min_token_count({ "t1" }));
   ASSERT_EQ(true, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_min_token_count({ "t1", "t2", "t3" }));
   ASSERT_EQ(true, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_min_token_count({ "t1", "t2", "t3", "t4", "t5", "t6", "t7" }));
}

TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest, assert_odd_token_count__will_return_false_if_the_number_of_tokens_is_not_odd)
{
   ASSERT_EQ(false, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_odd_token_count({ }));
   ASSERT_EQ(false, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_odd_token_count({ "t1", "t2" }));
   ASSERT_EQ(false, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_odd_token_count({ "t1", "t2", "t3", "t4", "t5", "t6" }));
}

TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest,
   assert_token_count_eq__will_return_true_if_the_number_of_tokens_is_equal_to_the_value)
{
   ASSERT_EQ(true, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_token_count_eq({ }, 0));
   ASSERT_EQ(true, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_token_count_eq({ "t1", "t2" }, 2));
   ASSERT_EQ(true, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_token_count_eq({ "t1", "t2", "t3", "t4", "t5", "t6" }, 6));
}

TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest,
   assert_token_count_eq__will_return_false_if_the_number_of_tokens_is_equal_to_the_value)
{
   ASSERT_EQ(false, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_token_count_eq({ }, 1));
   ASSERT_EQ(false, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_token_count_eq({ "t1", "t2" }, 999));
   ASSERT_EQ(false, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::assert_token_count_eq({ "t1", "t2", "t3", "t4", "t5", "t6" }, -1));
}

TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest,
   emit_script_event__will_emit_a_game_event_with_the_expected_name_and_data)
{
   // TODO
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptRunnerTest,
   play_or_resume__command_and_argument__will_trim_the_argument_fragment)
{
   // note this is a private method test
}

