/*
** std_effects.c for raytracer in /home/arthur/Projects/raytracer2/src/render/
**
** Made by Arthur Philippe
** Login   <arthur.philippe@epitech.eu>
**
** Started on  Mon Apr 17 16:14:09 2017 Arthur Philippe
** Last update Mon Apr 17 21:08:43 2017 Arthur Philippe
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

static void	prep_ray(t_render_in *in,
			 t_render_out *pr_out,
			 t_env *env)
{
  in->dir_vector.x = env->light.x - pr_out->hit_pt.x;
  in->dir_vector.y = env->light.y - pr_out->hit_pt.y;
  in->dir_vector.z = env->light.z - pr_out->hit_pt.z;
  in->eye_pt = pr_out->hit_pt;
  in->skip = pr_out->last_obj;
}

int		std_color_effect(t_env *env, t_render_out *pr_out)
{
  t_render_in	in;
  t_render_out	nw_out;

  my_memset(&in, 0, sizeof(t_render_in));
  prep_ray(&in, pr_out, env);
  objects_hit_attempt(env, &in, &nw_out);
  if (nw_out.k == 1)
    return (0);
  return (1);
}
