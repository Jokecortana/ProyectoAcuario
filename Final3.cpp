/*---------------------------------------------------------*/
/* ----------------  Proyecto                 -----------*/
/*-----------------    2023-1   ---------------------------*/
/*------------- Alumno:   ---------------*/
/*------------- No. Cuenta    ---------------*/
#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

//audio

#include <irrKlang.h>
using namespace irrklang; 

#pragma comment(lib, "winmm.lib")
bool	sound = true,
		sound2 = true,
		sound3 = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor *monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 100.0f, 500.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

// posiciones
//float x = 0.0f;
//float y = 0.0f;
float	movAuto_x = 0.0f,
movAuto_z = 0.0f,
orienta = 0.0f;
bool	animacion = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false;


//Keyframes (Manipulación y dibujo)
float	posX = 0.0f,
posY = 0.0f,
posZ = 0.0f,
rotRodIzq = 0.0f,
giroMonito = 0.0f;
float	incX = 0.0f,
incY = 0.0f,
incZ = 0.0f,
rotInc = 0.0f,
giroMonitoInc = 0.0f;

<<<<<<< HEAD
//variables mov pinguinos
float movPingu_x = 0.0f,
movPingu_z = 0.0f,
orientaPingu = 0.0f,
movPingu_x2 = 400.0f,
movPingu_z2 = 30.0f,
orientaPingu2 = 0.0f,
animalaspingu = 0.0f,
alaspingu = 0.0f,
animpataspingu = 0.0f,
pataspingu = 0.0f;

//variables cangrejos
float movcrab_x = -450.0f,
movcrab_z = 450.0f,
movcrab_y = 0.0f,
orientacrab = 0.0f,
animpatascrab = 0.0f,
patasbcrab = 0.0f,
animpinzascrab = 0.0f,
pinzascrab = 0.0f,
movcarrito_x = 0.0f,
movcarrito_z = 450.0f,
orientacarrito = 0.0f;

//animaciones pinguinos
bool animacionP = true,
reco1 = true,
reco2 = false,
reco3 = false,
reco4 = false,
animacionP2 = true,
reco5 = true,
reco6 = false,
reco7 = false,
reco8 = false,
reco9 = false;

//animacion carrito
bool animacionB = false,
re1 = true,
re2 = false,
re3 = false,
re4 = false,
re5 = false,
re6 = false,
re7 = false,
re8 = false,
re9 = false;

//animacion cangrejos
bool animacionC = false,
r1 = true,
r2 = false,
r3 = false,
r4 = false;







=======
>>>>>>> a3d6e5ef31c680d1eced8547fe8b4061f458863e
#define MAX_FRAMES 9
int i_max_steps = 60;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotRodIzq;
	float giroMonito;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	std::cout << "Frame Index = " << FrameIndex << std::endl;

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].giroMonito = giroMonito;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	giroMonito = KeyFrame[0].giroMonito;
}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

}

void animate(void)
{
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;

			rotRodIzq += rotInc;
			giroMonito += giroMonitoInc;

			i_curr_steps++;
		}
	}

<<<<<<< HEAD



	if (animacionP2) {
		//animacion alas

		if (animalaspingu == 0) {//CAMBIAR PIVOTE
			alaspingu += 1.0f;
			if (alaspingu >= 15) {
				animalaspingu = 1;
			}
		}
		else {
			alaspingu -= 1.0f;
			if (alaspingu <= -15) {
				animalaspingu = 0;
			}
		}

		//animacion patas

		if (animpataspingu == 0) {
			pataspingu += 1.0f;
			if (pataspingu >= 25) {
				animpataspingu = 1;
			}
		}
		else {
			pataspingu -= 1.0f;
			if (pataspingu <= -25) {
				animpataspingu = 0;
			}
		}




		//animacion recorrido
		if (reco5) {
			movPingu_x2 = 400.0f;
			movPingu_z2 += 1.0f;
			orientaPingu2 = 0.0f;
			if (movPingu_z2 >= 80.0f) {
				reco5 = false;
				reco6 = true;

			}

		}

		if (reco6) {
			movPingu_x2 += 1.0f;
			movPingu_z2 = 80.0f;
			orientaPingu2 = 90.0f;
			if (movPingu_x2 >= 435.0f) {
				reco6 = false;
				reco7 = true;

			}

		}

		if (reco7) {
			movPingu_x2 -= 0.7f;
			movPingu_z2 -= 1.0f;
			orientaPingu2 = -125.0f;
			if (movPingu_x2 <= 400.0f&&movPingu_z2 <= 30.0f) {
				reco7 = false;
				reco5 = true;

			}

		}










	}



	if (animacionC) {
		/*animacion patas
		if (animpatascrab == 0) {
			patasbcrab += 1.0f;
			if (patasbcrab >= 2) {
				animpatascrab = 1;
			}
		}
		else {
			patasbcrab -= 1.0f;
			if (patasbcrab <= -2) {
				animpatascrab = 0;
			}
		}

		//animacion pinzas

		if (animpinzascrab == 0) {
			pinzascrab += 1.0f;
			if (pinzascrab >= 1) {
				animpinzascrab = 1;
			}
		}
		else {
			pinzascrab -= 1.0f;
			if (pinzascrab <= -1) {
				animpinzascrab = 0;
			}
		}
		*/


		if (r1) {
			movcrab_x -= 1.0f;
			movcrab_z -= 1.0f;
			orientacrab = -45.0f;
			if (movcrab_x <= -400) {
				r1 = false;
				r2 = true;
			}




		}




	}



































=======
>>>>>>> a3d6e5ef31c680d1eced8547fe8b4061f458863e
	//Vehículo
	if (animacion)
	{
		movAuto_z += 3.0f;
	}
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

//audio
/*
void music(){
	if (sound) {
		bool played = PlaySound(L"Media/aves.wav", NULL, SND_LOOP | SND_ASYNC);
		sound = false;
	}
}

void music2() {
	if (sound) {
		bool played = PlaySound(L"Media/pinguino.wav", NULL, SND_LOOP | SND_ASYNC);
		sound2 = false;
	}
}

void music3() {
	if (sound) {
		bool played = PlaySound(L"Media/delfin.wav", NULL, SND_LOOP | SND_ASYNC);
		sound3 = false;
	}
}
*/

int main()
{

	//audio de olas, ambiental para todo el acuario 

	ISoundEngine* engine = createIrrKlangDevice();
	if (!engine)
		return 0;
	engine->play2D("Media/mar.wav", true);
	


	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights_mod.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	// -----------
	Model piso("resources/objects/piso/piso.obj");
	//Modelos Dylan
	Model fuente("resources/objects/Fuente1/f1.obj");
	Model valla("resources/objects/Vallas/valla1.obj");
	Model valla2("resources/objects/Vallas2/valla2.obj");
	Model crab("resources/objects/Crab1/crab1.obj");
	Model ping("resources/objects/pinguino1/pingu.obj");
	Model roc("resources/objects/Roca/roc1.obj");
	Model rocap("resources/objects/RocaP/rocap.obj");
	Model rocap1("resources/objects/RocaP1/rocap1.obj");
	Model cafe("resources/objects/cafeteria/cafe.obj");
	Model plat("resources/objects/plataforma/plat.obj");
	Model banc("resources/objects/banca/banc.obj");
	Model rest("resources/objects/restrooms/rest.obj");
	Model carro("resources/objects/helados/carro.obj");
	Model bin("resources/objects/bote/bin.obj");
	Model jaula("resources/objects/jaula/cge.obj");
	Model tienda("resources/objects/tienda/store.obj");
	


	//carro basura
	Model carrito("resources/objects/carrito/carro.obj");
	Model llantasd("resources/objects/carrito/llanta1.obj");
	Model llantaiz("resources/objects/carrito/llanta2.obj");
	Model llantasi("resources/objects/carrito/llanta3.obj");
	Model llantaid("resources/objects/carrito/llanta4.obj");

	/*
		ModelAnim employe("resources/objects/empleado/Thoughtful Head Shake.dae");
		employe.initShaders(animShader.ID); //aÃ±adir el objeto al shader de animacion

		ModelAnim p1("resources/objects/p1/Sitting Talking.dae");
		p1.initShaders(animShader.ID); //aÃ±adir el objeto al shader de animacion

		ModelAnim p2("resources/objects/p2/Talking.dae");
		p2.initShaders(animShader.ID); //aÃ±adir el objeto al shader de animacion

		ModelAnim p3("resources/objects/p3/Talking.dae");
		p3.initShaders(animShader.ID); //aÃ±adir el objeto al shader de animacion
		*/
		//Fin modelos Dylan


		//Modelos Ariadna
	Model fish1("resources/objects/Fish/fish1.obj");
	Model fish2("resources/objects/Fish/fish2.obj");
	Model fish3("resources/objects/Fish/fish3.obj");
	Model ave1("resources/objects/aves/ave1.obj");
	Model ave2("resources/objects/aves/ave2.obj");
	Model ave3("resources/objects/aves/ave3.obj");
	Model ave4("resources/objects/aves/ave4.obj");
	Model comida("resources/objects/comida/comida.obj");
	Model pecera("resources/objects/pecera/pecera.obj");




	//Modelos Miranda

		//Model tiburon1("resources/objects/Shark002OBJ/Correctshark002.obj");
	Model tiburon2("resources/objects/shark_obj/shark_01.obj");
<<<<<<< HEAD

=======
	Model delfin("resources/objects/delfin/10014_dolphin_v2_max2011_it2.obj");
	Model shark("resources/objects/shark/Shark_OBJ.obj");
	
>>>>>>> a3d6e5ef31c680d1eced8547fe8b4061f458863e



	//Fin modelos Miranda

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].giroMonito = 0;
	}

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(1.5f, 1.0f, 1.0f));
		staticShader.setFloat("pointLight[0].constant", 0.08f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(-80.0, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setVec3("spotLight[0].position", glm::vec3(0.0f, 20.0f, 10.0f));
		staticShader.setVec3("spotLight[0].direction", glm::vec3(0.0f, -1.0f, 0.0f));
		staticShader.setVec3("spotLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("spotLight[0].cutOff", glm::cos(glm::radians(10.0f)));
		staticShader.setFloat("spotLight[0].outerCutOff", glm::cos(glm::radians(60.0f)));
		staticShader.setFloat("spotLight[0].constant", 1.0f);
		staticShader.setFloat("spotLight[0].linear", 0.0009f);
		staticShader.setFloat("spotLight[0].quadratic", 0.0005f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(0.6f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);


		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------
		//Remember to activate the shader with the animation
		animShader.use();
		animShader.setMat4("projection", projection);
		animShader.setMat4("view", view);

		animShader.setVec3("material.specular", glm::vec3(0.5f));
		animShader.setFloat("material.shininess", 32.0f);
		animShader.setVec3("light.ambient", ambientColor);
		animShader.setVec3("light.diffuse", diffuseColor);
		animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		animShader.setVec3("light.direction", lightDirection);
		animShader.setVec3("viewPos", camera.Position);

		/*empleado
		model = glm::translate(glm::mat4(1.0f), glm::vec3(420.0f, 16.0f, 300.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		animShader.setMat4("model", model);
		//employe.Draw(animShader);


		//p1
		model = glm::translate(glm::mat4(1.0f), glm::vec3(330.0f, 20.0f, 400.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		animShader.setMat4("model", model);
		//p1.Draw(animShader);

		//p2
		model = glm::translate(glm::mat4(1.0f), glm::vec3(320.0f, 16.0f, 350.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		animShader.setMat4("model", model);
		//p2.Draw(animShader);

		//p3
		model = glm::translate(glm::mat4(1.0f), glm::vec3(320.0f, 16.0f, 300.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		animShader.setMat4("model", model);
		//p3.Draw(animShader);

		*/
		// ------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		piso.Draw(staticShader);


		//Modelos Dylan


//carrito
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcarrito_x, 0.0f, movcarrito_z));
		model = glm::rotate(model, glm::radians(orientacarrito), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		carrito.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcarrito_x, 0.0f, movcarrito_z));
		model = glm::rotate(model, glm::radians(orientacarrito), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		llantasd.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcarrito_x, 0.0f, movcarrito_z));
		model = glm::rotate(model, glm::radians(orientacarrito), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		llantaiz.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcarrito_x, 0.0f, movcarrito_z));
		model = glm::rotate(model, glm::radians(orientacarrito), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		llantasi.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movcarrito_x, 0.0f, movcarrito_z));
		model = glm::rotate(model, glm::radians(orientacarrito), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		llantaid.Draw(staticShader);

		//Fuente
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		fuente.Draw(staticShader);


		//Valla pinguinos
		model = glm::translate(glm::mat4(1.0f), glm::vec3(750.0f, 0.0f, -50.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		valla.Draw(staticShader);

		//Valla cangrejos
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 0.0f, 100.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		valla2.Draw(staticShader);

		//cangrejos
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-450.0f, 0.0f, 450.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		crab.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-430.0f, 0.0f, 410.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		crab.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 0.0f, 480.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		crab.Draw(staticShader);

		//ROCAS cangrejos
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-390.0f, 0.0f, 460.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		roc.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-420.0f, 0.0f, 460.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		roc.Draw(staticShader);



		//pinguinos
		model = glm::translate(glm::mat4(1.0f), glm::vec3(400.0f, 0.0f, 90.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		ping.Draw(staticShader);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(450.0f, 0.0f, 70.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		ping.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(390.0f, 0.0f, 40.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		ping.Draw(staticShader);

		//rocaPinguinos
		model = glm::translate(glm::mat4(1.0f), glm::vec3(390.0f, 0.0f, -5.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		rocap.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(390.0f, 0.0f, -1.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f));
		staticShader.setMat4("model", model);
		rocap1.Draw(staticShader);


		//cafeteria

		model = glm::translate(glm::mat4(1.0f), glm::vec3(420.0f, 16.0f, 300.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		cafe.Draw(staticShader);

		//plataforma

		model = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, 0.0f, 400.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f));
		staticShader.setMat4("model", model);
		plat.Draw(staticShader);


		//banca
		model = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 18.0f, 470.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		banc.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(350.0f, 18.0f, 300.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		banc.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, 18.0f, 400.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		banc.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(350.0f, 18.0f, 400.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		banc.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, 18.0f, 300.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		banc.Draw(staticShader);

		//restrooms
		model = glm::translate(glm::mat4(1.0f), glm::vec3(460.0f, 16.0f, 450.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		rest.Draw(staticShader);

		//carro de helados
		model = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, 17.0f, 250.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		carro.Draw(staticShader);

		//bote de basura
		model = glm::translate(glm::mat4(1.0f), glm::vec3(350.0f, 17.0f, 250.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		bin.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(460.0f, 17.0f, 400.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		bin.Draw(staticShader);

		//jaula
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-410.0f, 0.0f, 250.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(40.0f));
		staticShader.setMat4("model", model);
		jaula.Draw(staticShader);

		//tienda
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(13.0f));
		staticShader.setMat4("model", model);
		tienda.Draw(staticShader);


		//Fin Modelos Dylan


		//Modelos Miranda
		/*
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-390.0f, 0.0f, 270.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		tiburon1.Draw(staticShader);
		*/
		//tiburon2

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 10.0f, -500.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		tiburon2.Draw(staticShader);

<<<<<<< HEAD

=======
>>>>>>> a3d6e5ef31c680d1eced8547fe8b4061f458863e

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 10.0f, -300.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		delfin.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 10.0f, -200.0f));
		model = glm::rotate(model, glm::radians(-270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		delfin.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-500.0f, 10.0f, -100.0f));
		model = glm::rotate(model, glm::radians(-270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f));
		staticShader.setMat4("model", model);
		shark.Draw(staticShader);

		
		//Fin Modelos Miranda*/




	//Modelos Ariadna

	//peces
		model = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, 5.0f, -200.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		fish1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(60.0f, 5.0f, -200.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		fish2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(70.0f, 5.0f, -200.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		fish3.Draw(staticShader);

		//Aves
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-370.0f, 0.0f, 300.0f));
		model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		ave1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-470.0f, 0.0f, 230.0f));
		model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		ave1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 30.0f, 250.0f));
		model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		ave2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-350.0f, 90.0f, 300.0f));
		model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		ave2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 70.0f, 250.0f));
		model = glm::rotate(model, glm::radians(340.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		ave2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 50.0f, 200.0f));
		model = glm::rotate(model, glm::radians(340.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		ave3.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 90.0f, 200.0f));
		model = glm::rotate(model, glm::radians(300.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		ave3.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-360.0f, 40.0f, 310.0f));
		model = glm::rotate(model, glm::radians(280.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		ave3.Draw(staticShader);

		//Ãrea de comida
		//comida hamburguesa
		model = glm::translate(glm::mat4(1.0f), glm::vec3(290.0f, 30.0f, 465.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		comida.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(240.0f, 30.0f, 395.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		comida.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(340.0f, 30.0f, 295.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f));
		staticShader.setMat4("model", model);
		comida.Draw(staticShader);


		pecera.Draw(staticShader);





		//Fin Modelos Ariadna



		//Fin Modelos Ariadna

		// -------------------------------------------------------------------------------------------------------------------------
		// Carro
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(15.0f + movAuto_x, -1.0f, movAuto_z));
		tmp = model = glm::rotate(model, glm::radians(orienta), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		staticShader.setMat4("model", model);
		//carro.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(8.5f, 2.5f, 12.9f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		staticShader.setMat4("model", model);
		//llanta.Draw(staticShader);	//Izq delantera

		model = glm::translate(tmp, glm::vec3(-8.5f, 2.5f, 12.9f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		//llanta.Draw(staticShader);	//Der delantera

		model = glm::translate(tmp, glm::vec3(-8.5f, 2.5f, -14.5f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		//llanta.Draw(staticShader);	//Der trasera

		model = glm::translate(tmp, glm::vec3(8.5f, 2.5f, -14.5f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		staticShader.setMat4("model", model);
		//llanta.Draw(staticShader);	//Izq trase
		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje
		// -------------------------------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		tmp = model = glm::rotate(model, glm::radians(giroMonito), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		//torso.Draw(staticShader);

		//Pierna Der
		model = glm::translate(tmp, glm::vec3(-0.5f, 0.0f, -0.1f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		//piernaDer.Draw(staticShader);

		//Pie Der
		model = glm::translate(model, glm::vec3(0, -0.9f, -0.2f));
		staticShader.setMat4("model", model);
		//botaDer.Draw(staticShader);

		//Pierna Izq
		model = glm::translate(tmp, glm::vec3(0.5f, 0.0f, -0.1f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		//piernaIzq.Draw(staticShader);

		//Pie Iz
		model = glm::translate(model, glm::vec3(0, -0.9f, -0.2f));
		staticShader.setMat4("model", model);
		//botaDer.Draw(staticShader);	//Izq trase

		//Brazo derecho
		model = glm::translate(tmp, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.75f, 2.5f, 0));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		//brazoDer.Draw(staticShader);

		//Brazo izquierdo
		model = glm::translate(tmp, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.75f, 2.5f, 0));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		//brazoIzq.Draw(staticShader);

		//Cabeza
		model = glm::translate(tmp, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0));
		staticShader.setMat4("model", model);
		//cabeza.Draw(staticShader);


		
	

		// -------------------------------------------------------------------------------------------------------------------------
		// Caja Transparente --- Siguiente Práctica
		// -------------------------------------------------------------------------------------------------------------------------
		/*glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -70.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		staticShader.setMat4("model", model);
		cubo.Draw(staticShader);
		glEnable(GL_BLEND);*/
		// -------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	skybox.Terminate();
	glfwTerminate();
	engine->drop();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	//To Configure Model
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		posZ++;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		posZ--;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		posX--;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		posX++;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		rotRodIzq--;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		rotRodIzq++;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		giroMonito--;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		giroMonito++;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		lightPosition.x++;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		lightPosition.x--;

	//Car animation
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		animacion ^= true;
/*
	//sonido aves
	if (key == GLFW_KEY_O && action == GLFW_PRESS)
		music();


	//sonido pinguino
	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
		music2();
	//sonido delfines
	if (key == GLFW_KEY_K && action == GLFW_PRESS)
		music3();
*/
	//To play KeyFrame animation 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	//To Save a KeyFrame
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}