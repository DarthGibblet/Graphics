//Taken from http://myheroics.wordpress.com/2008/09/04/glsl-bloom-shader/
uniform sampler2D bgl_RenderedTexture;
uniform float runningTime;

void main()
{
//	gl_FragColor = texture2D(bg1_RenderedTexture, gl_TexCoord[0].st);
//	gl_FragColor = vec4(0.0, 0.25, 0.75, 1.0);

   vec4 sum = vec4(0);
   vec2 texcoord = vec2(gl_TexCoord[0]);
   int j;
   int i;

   for( i= -4 ;i < 4; i++)
   {
        for (j = -3; j < 3; j++)
        {
            sum += texture2D(bgl_RenderedTexture, texcoord + vec2(j, i)*0.004) * 0.25;
        }
   }
   
   if (texture2D(bgl_RenderedTexture, texcoord).r < 0.3)
   {
      gl_FragColor = sum*sum*0.006*(sin(runningTime)+1) + texture2D(bgl_RenderedTexture, texcoord);
   }
   else
   {
      if (texture2D(bgl_RenderedTexture, texcoord).r < 0.5)
      {
         gl_FragColor = sum*sum*0.0045*(sin(runningTime)+1) + texture2D(bgl_RenderedTexture, texcoord);
      }
      else
      {
         gl_FragColor = sum*sum*0.00375*(sin(runningTime)+1) + texture2D(bgl_RenderedTexture, texcoord);
      }
   }
}