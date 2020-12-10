----------------------fragmentShader-----------------------------------------------

in vec2 pass_textureCoordinates

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

out vec4 out_Color;

vec blendMapColour = texture(blendMap, pass_textureCoordinates);
float backTextureAmount = 1 - (blendMapColour.r, blendMapColour.g, blendMapColour.b);
vec2 tiledCoords = pass_textureCoordinates * 40.0;
vec4 backgroundTextureColour = texture(backgroundTexture, tiledCoords) * backTextureAmount;
vec4 rTextureColour = texture(rTexture, tiledCoords) * blendMapColour.r;
vec4 gTextureColour = texture(gTexture, tiledCoords) * blendMapColour.g;
vec4 bTextureColour = texture(bTexture, tiledCoords) * blendMapColour.b;

vec4 totalColour = backgroundTextureColour + rTextureColour + gTextureColour + bTextureColour;
out_Color = totalColour;

---------------------------------------vertexShader--------------------------------------------------




