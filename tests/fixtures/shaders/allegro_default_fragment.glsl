#ifdef GL_ES
precision lowp float;
#endif
uniform sampler2D al_tex;
uniform bool al_use_tex;
uniform bool al_alpha_test;
uniform int al_alpha_func;
uniform float al_alpha_test_val;
varying vec4 varying_color;
varying vec2 varying_texcoord;

bool alpha_test_func(float x, int op, float compare);

void main()
{
  vec4 c;
  if (al_use_tex)
    c = varying_color * texture2D(al_tex, varying_texcoord);
  else
    c = varying_color;
  if (!al_alpha_test || alpha_test_func(c.a, al_alpha_func, al_alpha_test_val))
    gl_FragColor = c;   // For the purposes of the test, this is the original line
  else
    discard;
}

bool alpha_test_func(float x, int op, float compare)
{
  if (op == 0) return false;
  else if (op == 1) return true;
  else if (op == 2) return x < compare;
  else if (op == 3) return x == compare;
  else if (op == 4) return x <= compare;
  else if (op == 5) return x > compare;
  else if (op == 6) return x != compare;
  else if (op == 7) return x >= compare;
  return false;
}
