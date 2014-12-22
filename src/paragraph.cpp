/*

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include <allegro_flare/useful.h>
#include <allegro_flare/object2d.h>
#include <allegro_flare/paragraph.h>

//#include <allegro_flare/framework.h>

#include <vector>



#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))




WordWidthText::WordWidthText(std::string full_text, ALLEGRO_FONT *font)
// font is assumed to be valid
// the input text is assumed not contain any return characters
{
	this->font = font;
	word.clear();
	width.clear();
	this->full_text = full_text;
	width_of_space = al_get_text_width(font, " ");
	word = php::explode(" ", full_text);
	for (int i=0; i<(int)word.size(); i++) width.push_back(al_get_text_width(font, word[i].c_str()));
}

void WordWidthText::change_font(ALLEGRO_FONT *font)
// assumes a valid font
{
	this->font = font;
	width.clear();
	for (int i=0; i<(int)word.size(); i++) width.push_back(al_get_text_width(this->font, word[i].c_str()));
}

std::pair<int, int> WordWidthText::find_word_and_char(int cursor)
// todo: this would be effecient as a binary search
{
	int word_num = 0, word_char_num = 0, cursor_ct = 0;

	// find the word
	for (int w=0; w<(int)word.size(); w++)
	{
		cursor_ct += word[w].length() + 1;
		if (cursor_ct > cursor)
		{
			word_num = w;
			word_char_num = cursor - (cursor_ct - word[w].length() - 1);// ;
			return std::pair<int, int>(word_num, word_char_num);
		}
	}

	return std::pair<int, int>(0, 0);
}

void WordWidthText::insert(int cursor, std::string str)
// the cursor is assumed to be within bounds
// and the inserted text is assumed not to have any return characters
{
	// insert the string into full_text
	full_text.insert(cursor, str);

	// insert the string into word
	std::pair<int, int> word_char = find_word_and_char(cursor);
	word[word_char.first].insert(word_char.second, str);

	// create a new word set and width set from the new string
	std::vector<std::string> _word = php::explode(" ", word[word_char.first]);
	std::vector<int> _width;
	for (int i=0; i<(int)_word.size(); i++) _width.push_back(al_get_text_width(font, _word[i].c_str()));

	// erase the existing word and width
	word.erase(word.begin()+word_char.first);
	width.erase(width.begin()+word_char.first);

	// insert the new word and width sets
	word.insert(word.begin()+word_char.first, _word.begin(), _word.end());
	width.insert(width.begin()+word_char.first, _width.begin(), _width.end());
}

void WordWidthText::erase(int cursor_start, int cursor_end)
// the cursors are assumed to be within the bounds
// and cursor_end is assumed to be larger or equal to cursor_start
{
	// erase the string from the full_text
	full_text.erase(full_text.begin()+cursor_start, full_text.begin()+cursor_end);

	// create new string from the first half of the start word,
	// and the second half of the end word
	std::pair<int, int> start_word_char = find_word_and_char(cursor_start);
	std::pair<int, int> end_word_char = find_word_and_char(cursor_end);
	std::string composite_word = word[start_word_char.first].substr(0, start_word_char.second)
		+ word[end_word_char.first].substr(end_word_char.second);

	// remove from the start word to the end word
	word.erase(word.begin()+start_word_char.first, word.begin()+end_word_char.first+1);
	width.erase(width.begin()+start_word_char.first, width.begin()+end_word_char.first+1);

	// insert the new string into word
	word.insert(word.begin()+start_word_char.first, composite_word);
	width.insert(width.begin()+start_word_char.first, al_get_text_width(font, composite_word.c_str()));
}



*/






/*

better_paragraph::better_paragraph(float x, float y, float w, float h, ALLEGRO_FONT *font)
    : object2d(x, y, w, h)
	, WordWidthText("Type your text here.", font)
	, start_cursor(0)
	, end_cursor(0)
	, line_height(al_get_font_line_height(font))
	, _text_align(TEXT_ALIGN_CENTER)
{ }

void better_paragraph::insert(std::string str)
{
	WordWidthText::insert(start_cursor, str);
}

void better_paragraph::change_font(ALLEGRO_FONT *font)
{
	this->WordWidthText::change_font(font);
	line_height = al_get_font_line_height(font);
}

void better_paragraph::text_align(text_align_t align)
{
	_text_align = align;
}

#include <allegro_fire/useful.h>


void better_paragraph::draw(bool show_bounding_box, bool show_origin)
{
	if (_placement) _placement->start_transform();

	if (show_bounding_box)
	{
		float a = 0.2;
		if (_appearance) a *= _appearance->opacity;
		//if (mouse_over)
		////al_draw_rectangle(left(), top(), right(), bottom(), al_map_rgba_f(0,0,0,1.0), 1.0);
		al_draw_rectangle(0, 0, *_w, *_h, al_map_rgba_f(0,0,0,1.0), 1.0);
	}

	////int x_cursor = left();
	int x_cursor = 0;
	int y_cursor = 0;
	int line = 0;
	std::pair<int, int> cursor_word_char = find_word_and_char(start_cursor);
	std::pair<int, int> cursor_word_char2 = find_word_and_char(end_cursor);

	word_line_start.clear();

	ALLEGRO_COLOR text_color = al_color_name("black");
	if (_appearance) text_color = ::color(text_color, _appearance->opacity);

	for (int i=0; i<(int)word.size(); i++)
	{
		////if ((x_cursor + width[i] + width_of_space) > (right()))
		if ((x_cursor + width[i] + width_of_space) > *_w)
		{
			////x_cursor = left();
			x_cursor = 0;
			line++;
			word_line_start.push_back(i);
		}

		////y_cursor = line_height * line + top();
		y_cursor = line_height * line + 0;
		if (cursor_word_char.first == i)
		{
			int type_cursor_x = al_get_text_width(font, word[i].substr(0, cursor_word_char.second).c_str())
				//+ left_edge;
				+ x_cursor;
			//al_draw_filled_rectangle(x_cursor, y_cursor, x_cursor+p->width[i], y_cursor+al_get_font_line_height(p->font), al_color_name("lightblue"));
			int line_middle = y_cursor+al_get_font_line_height(font)/2;
			int half_lh = al_get_font_line_height(font)/2;
			al_draw_line(type_cursor_x, line_middle-half_lh-2, type_cursor_x, line_middle, al_color_name("black"), 1.0);
			al_draw_line(type_cursor_x-3, line_middle-half_lh-2, type_cursor_x+3, line_middle-half_lh-2, al_color_name("black"), 1.0);
		}
		if (cursor_word_char2.first == i)
		{
			int type_cursor_x = al_get_text_width(font, word[i].substr(0, cursor_word_char2.second).c_str())
				//+ left_edge;
				+ x_cursor;
			//al_draw_filled_rectangle(x_cursor, y_cursor, x_cursor+p->width[i], y_cursor+al_get_font_line_height(p->font), al_color_name("lightblue"));
			int line_middle = y_cursor+al_get_font_line_height(font)/2;
			int half_lh = al_get_font_line_height(font)/2;
			al_draw_line(type_cursor_x, line_middle, type_cursor_x, line_middle+half_lh+2, al_color_name("black"), 1.0);
			al_draw_line(type_cursor_x-3, line_middle+half_lh+2, type_cursor_x+3, line_middle+half_lh+2, al_color_name("black"), 1.0);
		}

		al_draw_text(font, text_color, x_cursor, y_cursor, NULL, word[i].c_str());
		x_cursor += width[i] + width_of_space;
	}

	////if (show_origin) draw_crosshair(left(), top(), al_color_name("gray"));
	if (_placement) _placement->restore_transform();

	//if (show_origin) draw_crosshair(*_x, *_y, al_color_name("gray"));


	//std::string message = "lines: " + tostring(word_line_start.size()+1);
	//al_draw_text(get_font("lacuna.ttf", -19), al_color_name("black"), right(), bottom(), ALLEGRO_ALIGN_RIGHT, message.c_str());
}

void better_paragraph::on_key_char()
{
	switch(current_event->keyboard.keycode)
	{
	case ALLEGRO_KEY_RIGHT:
		if (current_event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT)
		{
			end_cursor++;
		}
		else
		{
			start_cursor++;
			end_cursor++;
		}
		break;
	case ALLEGRO_KEY_LEFT:
		if (current_event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT)
		{
			end_cursor--;
		}
		else
		{
			start_cursor--;
			end_cursor--;
		}
		break;
	case ALLEGRO_KEY_DELETE:
		if (start_cursor == end_cursor && start_cursor < (int)full_text.size())
		{
			erase(min(start_cursor, end_cursor), max(start_cursor, end_cursor)+1);
		}
		else
		{
			erase(min(start_cursor, end_cursor), max(start_cursor, end_cursor));
			end_cursor = min(start_cursor, end_cursor);
			start_cursor = end_cursor;
		}
		break;
	case ALLEGRO_KEY_BACKSPACE:
		if ((start_cursor == end_cursor) && (start_cursor > 0))
		{
			erase(min(start_cursor, end_cursor)-1, max(start_cursor, end_cursor));
			start_cursor--;
			end_cursor--;
		}
		else
		{
			erase(min(start_cursor, end_cursor), max(start_cursor, end_cursor));
			end_cursor = min(start_cursor, end_cursor);
			start_cursor = end_cursor;
		}
		break;
	default:
		if (current_event->keyboard.unichar >= 32 && current_event->keyboard.unichar <= 126)
		{
			insert(tostring((char)current_event->keyboard.unichar));
			start_cursor++;
			end_cursor++;
		}
	}

	start_cursor = limit(0, (int)full_text.size(), start_cursor);
	end_cursor = limit(0, (int)full_text.size(), end_cursor);
}









better_paragraph &new_better_paragraph(float x, float y, float w, float h, const char *id)
{
	return *static_cast<better_paragraph *>(object[id] = new better_paragraph(x, y, w, h));
}

better_paragraph &get_better_paragraph(const char *id)
{
	return *static_cast<better_paragraph *>(&get_object2d_by_id(id));
}


*/