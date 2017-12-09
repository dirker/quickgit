#include <cstdio>
#include <cstdlib>

#include <git2.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"

static void check_error(int error_code, const char *msg)
{
	if (!error_code)
		return;

	printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

static void error_callback(int error, const char *description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int argc, char *argv[])
{
	int error;

	// Setup window
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return EXIT_FAILURE;

	GLFWwindow *window = glfwCreateWindow(1280, 720, "QuickGit", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Setup ImGui binding
	ImGui_ImplGlfwGL2_Init(window, true);

	git_libgit2_init();

	git_repository *repo = NULL;
	error = git_repository_open(&repo, ".");
	check_error(error, "opening repository");

	git_revwalk *revwalk;

	error = git_revwalk_new(&revwalk, repo);
	check_error(error, "creating revwalk");

	error = git_revwalk_push_head(revwalk);
	check_error(error, "filling revwalk");

	git_oid oid;
	while (git_revwalk_next(&oid, revwalk) == 0) {
		char id[GIT_OID_HEXSZ+1];
		git_oid_tostr(id, sizeof(id), &oid);
		printf("%s\n", id);
	}

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		ImGui_ImplGlfwGL2_NewFrame();

		// Simple window
		{
			ImGui::Text("Hello, world!");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		// Rendering
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
		ImGui::Render();
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplGlfwGL2_Shutdown();
	glfwTerminate();

	printf("Bye.\n");
	return EXIT_SUCCESS;
}
