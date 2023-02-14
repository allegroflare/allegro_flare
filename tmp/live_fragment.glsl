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
  {
    c = varying_color * texture2D(al_tex, varying_texcoord);
  }
  else
  {
    c = varying_color;
  }

  if (!al_alpha_test || alpha_test_func(c.a, al_alpha_func, al_alpha_test_val))
  {
    vec3 color = c.rgb;
    vec3 blackPoint = vec3(0.02, 0.03, 0.3);
    //vec3 whitePoint = vec3(0.9, 0.9, 0.9);

    ////Calculate the distance from the black point and scale the color based on 
    ////the distance from the black point
    float black_point_distance = length(color.rgb - blackPoint.rgb);
    color.rgb = mix(blackPoint, color.rgb, smoothstep(0.0, 1.0, black_point_distance));

    // Calculate the distance from the white point and scale the color based on 
    // the distance from the black point
    //float white_point_distance = length(whitePoint.rgb - color.rgb);
    //color.rgb = mix(color.rgb, whitePoint, smoothstep(0.0, 1.0, white_point_distance));

    float a = 1.0;
    gl_FragColor = vec4(color, a); 
  }
  else
  {
    discard;
  }
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
