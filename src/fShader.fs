#version 330 core

struct Material {
       vec3 ambient;
       vec3 diffuse;
       vec3 specular;
       float shininess;
};

struct Light {
       vec3 position;
       vec3 ambient;
       vec3 diffuse;
       vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform Light light;
uniform Material material;

uniform vec3 objectColor;
uniform vec3 viewPos;

/* unused
   uniform vec3 lightPos;
   uniform vec3 lightColor;
*/

void main() {

     // ambient light
     float ambientStrength = 0.1;
     vec3 ambient = light.ambient * material.ambient;

     // light direction
     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(light.position - FragPos);

     // diffuse light
     float diff = max(dot(norm, lightDir), 0.0);
     vec3 diffuse = (diff * material.diffuse) * light.diffuse;

     // specular light
     float specularStrength = 0.5;
     vec3 viewDir = normalize(viewPos - FragPos);
     vec3 reflectDir = reflect(-lightDir, norm);
     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
     vec3 specular = (spec * material.specular) * light.specular;

     vec3 result = ambient + diffuse + specular;

     FragColor = vec4(result, 1.0);
}
