/* Orx - Portable Game Engine
 *
 * Copyright (c) 2008-2018 Orx-Project
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source
 *    distribution.
 */

/**
 * @file ufo.cpp
 * @date 17/05/2017
 * @author sausage@zeta.org.au
 *
 * Orx Game template
 */


#include "orx.h"
const orxFLOAT FORCE = 1.8;
orxCAMERA *camera;
//
orxOBJECT *ufoYouWinTextObject;
orxOBJECT *scoreObject;
orxOBJECT *ufo;
int score = 0;


/*
 * This is a basic C++ template to quickly and easily get started with a project or tutorial.
 */
orxSTATUS orxFASTCALL PhysicsEventHandler(const orxEVENT *_pstEvent)
{
 
  if (_pstEvent->eID == orxPHYSICS_EVENT_CONTACT_ADD) {
    orxOBJECT *pstRecipientObject, *pstSenderObject;
 
    /* Gets colliding objects */
    pstRecipientObject = orxOBJECT(_pstEvent->hRecipient);
    pstSenderObject = orxOBJECT(_pstEvent->hSender);
 
    const orxSTRING recipientName = orxObject_GetName(pstRecipientObject);
    const orxSTRING senderName = orxObject_GetName(pstSenderObject);
 
    if (orxString_SearchString(recipientName, "PickupObject") != orxNULL) {
      orxObject_SetLifeTime(pstRecipientObject, 0);
      orxObject_AddSound(pstSenderObject, "PickupSound");
      score += 150;
    }
 
    if (orxString_SearchString(senderName, "PickupObject") != orxNULL) {
      orxObject_SetLifeTime(pstSenderObject, 0);
      orxObject_AddSound(pstRecipientObject, "PickupSound");
      score += 150;
    }
    if (orxObject_IsEnabled(ufoYouWinTextObject) == orxFALSE && score == 1200) {
       orxObject_Enable(ufoYouWinTextObject, orxTRUE);
    }
  }
 
  return orxSTATUS_SUCCESS;
}


void orxFASTCALL Update(const orxCLOCK_INFO *_pstClockInfo, void *_pContext)
{
  if (ufo) {
 
	const orxFLOAT FORCE = 0.8;
 
	orxVECTOR rightForce = { FORCE, 0, 0 };
	orxVECTOR leftForce = { -FORCE, 0, 0 };
	orxVECTOR upForce = { 0, -FORCE, 0 };
	orxVECTOR downForce = { 0, FORCE, 0 };
 
	if (orxInput_IsActive("GoLeft")) {
		orxObject_ApplyForce(ufo, &leftForce, orxNULL);
	}
	if (orxInput_IsActive("GoRight")) {
		orxObject_ApplyForce(ufo, &rightForce, orxNULL);
	}
	if (orxInput_IsActive("GoUp")) {
		orxObject_ApplyForce(ufo, &upForce, orxNULL);
	}
	if (orxInput_IsActive("GoDown")) {
		orxObject_ApplyForce(ufo, &downForce, orxNULL);
	}
  }
if (scoreObject) {
  orxCHAR formattedScore[5];
  orxString_Print(formattedScore, "%d", score);
 
  orxObject_SetTextString(scoreObject, formattedScore);
 }
}


/** Initializes your game
 */
orxSTATUS orxFASTCALL Init()
{
    /* Displays a small hint in console */
    orxLOG("\n* This template creates a viewport/camera couple and an object"
    "\n* You can play with the config parameters in ../data/config/ufo.ini"
    "\n* After changing them, relaunch the template to see the changes.");
        orxVIEWPORT *viewport = orxViewport_CreateFromConfig("Viewport");
	camera = orxViewport_GetCamera(viewport);

	orxObject_CreateFromConfig("BackgroundObject");
	
	ufo = orxObject_CreateFromConfig("UfoObject");
	orxCamera_SetParent(camera, ufo);

	orxObject_CreateFromConfig("PickupObjects");
	orxObject_CreateFromConfig("ScoreObject");

	orxClock_Register(orxClock_FindFirst(orx2F(-1.0f), orxCLOCK_TYPE_CORE), Update, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);
	orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS, PhysicsEventHandler);

	scoreObject = orxObject_CreateFromConfig("ScoreObject");

	ufoYouWinTextObject = orxObject_CreateFromConfig("YouWinObject");
	orxObject_SetParent(ufoYouWinTextObject, ufo);
	orxObject_Enable(ufoYouWinTextObject, orxFALSE);
	//
	return orxSTATUS_SUCCESS;
}


/** Run function, is called every clock cycle
 */
orxSTATUS orxFASTCALL Run()
{
    orxSTATUS eResult = orxSTATUS_SUCCESS;

    /* Should quit? */
    if(orxInput_IsActive("Quit"))
    {
        /* Updates result */
        eResult = orxSTATUS_FAILURE;
    }

    /* Done! */
    return eResult;
}

/** Exit function
 */
void orxFASTCALL Exit()
{
    /* Lets Orx clean all our mess automatically. :) */
}

/** Bootstrap function
 */
orxSTATUS orxFASTCALL Bootstrap()
{
    orxSTATUS eResult = orxSTATUS_SUCCESS;

    /* Adds a config storage to find the initial config file */
    orxResource_AddStorage(orxCONFIG_KZ_RESOURCE_GROUP, "../data/config", orxFALSE);

    /* Done! */
    return eResult;
}

/** Main function
 */
int main(int argc, char **argv)
{
    /* Sets bootstrap function to provide at least one resource storage before loading any config files */
    orxConfig_SetBootstrap(Bootstrap);

    /* Executes a new instance of tutorial */
    orx_Execute(argc, argv, Init, Run, Exit);

    /* Done! */
    return EXIT_SUCCESS;
}
