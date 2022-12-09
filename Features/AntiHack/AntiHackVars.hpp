namespace AntiHackV
{
	namespace FlyHack
	{
		float flyhackPauseTime = 0.0f;

		// Token: 0x04000530 RID: 1328

		float flyhackDistanceVertical = 0.0f;
		float flyhackDistanceVerticalMax = 0.0f;
		// Token: 0x04000531 RID: 1329

		float flyhackDistanceHorizontal = 0.0f;
		float flyhackDistanceHorizontalMax = 0.0f;

	
		static float flyhack_penalty = 100.f;
	    static float flyhack_forgiveness_vertical = 1.5f;
		static float flyhack_forgiveness_vertical_inertia = 10.f;


		static float flyhack_forgiveness_horizontal = 1.5f;


		static float flyhack_forgiveness_horizontal_inertia = 10.f;

		static float flyhack_extrusion = 2.f;

		static float flyhack_margin = 0.05f;

		static float flyhack_stepsize = 0.1f;


		static int flyhack_maxsteps = 15;
	}
}