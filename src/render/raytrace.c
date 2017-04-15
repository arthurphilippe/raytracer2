/*
** raytrace.c for raytracer in /home/arthur/Projects/raytracer2/src/render/
**
** Made by Arthur Philippe
** Login   <arthur.philippe@epitech.eu>
**
** Started on  Sat Apr 15 13:26:22 2017 Arthur Philippe
** Last update Sat Apr 15 16:50:29 2017 Arthur Philippe
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <unistd.h>
#include "acp.h"
#include "raytracer.h"
#include "raytracer_messages.h"
#include "raytracer_data.h"
#include "launch.h"

static void	objects_hit_attempt(t_env *env,
				    t_render_in *in,
				    t_render_out *out)
{
  t_object		*objs;
  float			k;

  objs = env->objects;
  my_memset(out, 0, sizeof(t_render_out));
  out->k = -1;
  k = -1;
  while (objs)
    {
      k = obj_fctn_shunter(objs, in);
      if (k >= 0 && (out->k == -1 || out->k > k))
	out->k = k;
      objs = objs->next;
    }
  out->k = (out->k >= 0) ? out->k : 0;
}

static void	prep_ray(t_render_in *in,
			 t_env *env,
			 sfVector2i px)
{
  my_memset(in, 0, sizeof(t_render_in));
  in->dir_vector = calc_dir_vector(SC_W, env->screen_size, px);
  in->dir_vector = rotate_xyz(in->dir_vector, env->eye_rt);
  in->eye_pt = env->eye_pt;
}

void		raytrace_full_scene(t_env *env)
{
  int		total_px;
  t_render_in	in;
  t_render_out	out;
  sfVector2i	px;

  total_px = 0;
  px.x = 0;
  px.y = 0;
  while (px.y < SC_H)
    {
      if (total_px >= SC_W * SC_H / 10)
	{
	  acp_print("%c", LOAD_CHAR);
	  total_px = 0;
	}
      prep_ray(&in, env, px);
      objects_hit_attempt(env, &in, &out);
      if (out.k > 0)
	printf("out: %f - %d\n", out.k, out.last_obj);
      px.y = (px.x < SC_W) ? px.y : px.y + 1;
      px.x = (px.x < SC_W) ? px.x + 1 : 0;
      total_px += 1;
    }
}
