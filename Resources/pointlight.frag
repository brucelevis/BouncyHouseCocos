#ifdef GL_ES
precision highp float;
#endif

//uniform vec2 u_spritePosInSheet;
//uniform vec2 u_spriteSizeRelToSheet;
//uniform vec2 u_spriteOffset;
//uniform int  u_spriteRotated;
varying vec2 v_texCoord;
//uniform sampler2D u_normals;
//uniform vec2  u_contentSize;
//uniform float u_zOrder;


//uniform int u_lightActive0;
//uniform vec3  u_lightPos0;
//uniform vec3  u_lightColor0;
//uniform vec3  u_ambientColor0;
//uniform float  u_brightness0;
//uniform float u_cutoffRadius0;
//uniform float u_halfRadius0;
//
//uniform int u_lightActive1;
//uniform vec3  u_lightPos1;
//uniform vec3  u_lightColor1;
//uniform vec3  u_ambientColor1;
//uniform float  u_brightness1;
//uniform float u_cutoffRadius1;
//uniform float u_halfRadius1;
//
//uniform int u_lightActive2;
//uniform vec3  u_lightPos2;
//uniform vec3  u_lightColor2;
//uniform vec3  u_ambientColor2;
//uniform float  u_brightness2;
//uniform float u_cutoffRadius2;
//uniform float u_halfRadius2;
//
//uniform int u_lightActive3;
//uniform vec3  u_lightPos3;
//uniform vec3  u_lightColor3;
//uniform vec3  u_ambientColor3;
//uniform float  u_brightness3;
//uniform float u_cutoffRadius3;
//uniform float u_halfRadius3;
//
//uniform int u_lightActive4;
//uniform vec3  u_lightPos4;
//uniform vec3  u_lightColor4;
//uniform vec3  u_ambientColor4;
//uniform float  u_brightness4;
//uniform float u_cutoffRadius4;
//uniform float u_halfRadius4;

void main(void)
{
    vec4 texColor=texture2D(CC_Texture0, v_texCoord);
    gl_FragColor = texColor;
//    vec3 normal=texture2D(u_normals, v_texCoord).rgb;
//    normal=normal*2.0-1.0;
//    
//    vec2 spriteTexCoord = (v_texCoord - u_spritePosInSheet) / u_spriteSizeRelToSheet; // [0..1]
//    vec2 pixelPos = spriteTexCoord * u_contentSize + u_spriteOffset; // [0..origSize]
//    vec3 curPixelPosInLocalSpace = (u_spriteRotated == 1) ? vec3(pixelPos.y, pixelPos.x, 0.0)                    // origin: bottom-left
//    : vec3(pixelPos.x, u_contentSize.y - pixelPos.y, 0.0);

    
//    gl_FragColor = vec4( vec3( 0.0, 0.0, 0.0 ), texColor.a );
//
//    if ( u_lightActive0 == 1 )
//    {
//        vec3 lightVec = curPixelPosInLocalSpace - u_lightPos0;
//        vec3 posToLight = -normalize(lightVec);
//        float normDotPosToLight=max(0.0,dot(normal,posToLight));
//        
//        float intercept = u_cutoffRadius0 * u_halfRadius0;
//        float dx_1 = 0.5 / intercept;
//        float dx_2 = 0.5 / (u_cutoffRadius0 - intercept);
//        float offset = 0.5 + intercept * dx_2;
//        float lightDist = length(lightVec);
//        float falloffTermNear = clamp((1.0 - lightDist * dx_1), 0.0, 1.0);
//        float falloffTermFar  = clamp((offset - lightDist * dx_2), 0.0, 1.0);
//        float falloffSelect = step(intercept, lightDist);
//        float falloffTerm = (1.0 - falloffSelect) * falloffTermNear + falloffSelect * falloffTermFar;
//        
//        vec3 diffuse = normDotPosToLight * u_brightness0 * falloffTerm * u_lightColor0;
//        gl_FragColor += vec4(texColor.rgb * diffuse, texColor.a);
//    }
//    if ( u_lightActive1 == 1 )
//    {
//        vec3 lightVec = curPixelPosInLocalSpace - u_lightPos1;
//        vec3 posToLight = -normalize(lightVec);
//        float normDotPosToLight=max(0.0,dot(normal,posToLight));
//        
//        float intercept = u_cutoffRadius1 * u_halfRadius1;
//        float dx_1 = 0.5 / intercept;
//        float dx_2 = 0.5 / (u_cutoffRadius1 - intercept);
//        float offset = 0.5 + intercept * dx_2;
//        float lightDist = length(lightVec);
//        float falloffTermNear = clamp((1.0 - lightDist * dx_1), 0.0, 1.0);
//        float falloffTermFar  = clamp((offset - lightDist * dx_2), 0.0, 1.0);
//        float falloffSelect = step(intercept, lightDist);
//        float falloffTerm = (1.0 - falloffSelect) * falloffTermNear + falloffSelect * falloffTermFar;
//        
//        vec3 diffuse = normDotPosToLight * u_brightness1 * falloffTerm * u_lightColor1;
//        gl_FragColor += vec4(texColor.rgb * diffuse, texColor.a);
//    }
//    if ( u_lightActive2 == 1 )
//    {
//        vec3 lightVec = curPixelPosInLocalSpace - u_lightPos2;
//        vec3 posToLight = -normalize(lightVec);
//        float normDotPosToLight=max(0.0,dot(normal,posToLight));
//        
//        float intercept = u_cutoffRadius2 * u_halfRadius2;
//        float dx_1 = 0.5 / intercept;
//        float dx_2 = 0.5 / (u_cutoffRadius2 - intercept);
//        float offset = 0.5 + intercept * dx_2;
//        float lightDist = length(lightVec);
//        float falloffTermNear = clamp((1.0 - lightDist * dx_1), 0.0, 1.0);
//        float falloffTermFar  = clamp((offset - lightDist * dx_2), 0.0, 1.0);
//        float falloffSelect = step(intercept, lightDist);
//        float falloffTerm = (1.0 - falloffSelect) * falloffTermNear + falloffSelect * falloffTermFar;
//        
//        vec3 diffuse = normDotPosToLight * u_brightness2 * falloffTerm * u_lightColor2;
//        gl_FragColor += vec4(texColor.rgb * diffuse, texColor.a);
//    }
//    if ( u_lightActive3 == 1 )
//    {
//        vec3 lightVec = curPixelPosInLocalSpace - u_lightPos3;
//        vec3 posToLight = -normalize(lightVec);
//        float normDotPosToLight=max(0.0,dot(normal,posToLight));
//        
//        float intercept = u_cutoffRadius3 * u_halfRadius3;
//        float dx_1 = 0.5 / intercept;
//        float dx_2 = 0.5 / (u_cutoffRadius3 - intercept);
//        float offset = 0.5 + intercept * dx_2;
//        float lightDist = length(lightVec);
//        float falloffTermNear = clamp((1.0 - lightDist * dx_1), 0.0, 1.0);
//        float falloffTermFar  = clamp((offset - lightDist * dx_2), 0.0, 1.0);
//        float falloffSelect = step(intercept, lightDist);
//        float falloffTerm = (1.0 - falloffSelect) * falloffTermNear + falloffSelect * falloffTermFar;
//        
//        vec3 diffuse = normDotPosToLight * u_brightness3 * falloffTerm * u_lightColor3;
//        gl_FragColor += vec4(texColor.rgb * diffuse, texColor.a);
//    }
//    if ( u_lightActive4 == 1 )
//    {
//        vec3 lightVec = curPixelPosInLocalSpace - u_lightPos4;
//        vec3 posToLight = -normalize(lightVec);
//        float normDotPosToLight=max(0.0,dot(normal,posToLight));
//        
//        float intercept = u_cutoffRadius4 * u_halfRadius4;
//        float dx_1 = 0.5 / intercept;
//        float dx_2 = 0.5 / (u_cutoffRadius4 - intercept);
//        float offset = 0.5 + intercept * dx_2;
//        float lightDist = length(lightVec);
//        float falloffTermNear = clamp((1.0 - lightDist * dx_1), 0.0, 1.0);
//        float falloffTermFar  = clamp((offset - lightDist * dx_2), 0.0, 1.0);
//        float falloffSelect = step(intercept, lightDist);
//        float falloffTerm = (1.0 - falloffSelect) * falloffTermNear + falloffSelect * falloffTermFar;
//        
//        vec3 diffuse = normDotPosToLight * u_brightness4 * falloffTerm * u_lightColor4;
//        gl_FragColor += vec4(texColor.rgb * diffuse, texColor.a);
//    }
}