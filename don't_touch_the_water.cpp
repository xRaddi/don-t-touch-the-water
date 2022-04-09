/******* Don't touch the water *******
***************************************/

/**** INCLUDES ****/

#include <amxmodx>
#include <engine>

/**** CVARS ****/
new cvar_watermode, cvar_kickmessage, water_push

/**** Plugin Start ****/

public plugin_init()
{
	register_plugin("Don't touch the water", "1.4", "Raddish")
	
	/************* Water modes **************/
	/**** [| 1 PUSH | 2 SLAY | 3 KICK |] ****/
	
	cvar_watermode = register_cvar("amx_watermode", "1")
	
	/************* Cutom Message KICK **************/
	/****** Default: "Don't touch the water" *******/
	
	cvar_kickmessage = register_cvar("amx_water_msgkick", "Don't touch the water.")
	
	/************* Push the player out of water **************/
	/****************** Default: 25.0 ******************/
	
	water_push = register_cvar("amx_water_push", "25.0")
}

public client_PreThink(id)
{
	if(get_entity_flags(id) & FL_INWATER)
    {
		static Float:flVelocity[3]
		switch(get_pcvar_num(cvar_watermode))
		{
			case 1:
			{
				get_user_velocity(id, flVelocity)
				flVelocity[2] += get_pcvar_float(water_push)
				set_user_velocity(id, flVelocity)
			}
			case 2: user_kill(id, 0)
			case 3: 
			{
				static szMessage[64]
				get_pcvar_string(cvar_kickmessage, szMessage, charsmax(szMessage))
				
				message_begin(MSG_ONE, SVC_DISCONNECT, _, id)
				write_string(szMessage)
				message_end()
			}
		}
	}
}
