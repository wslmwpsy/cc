#pragma once

enum _EaxPresets {
	None = 0,
	Generic,
	PaddedCell,
	Room,
	Bathroom,
	LivingRoom,
	StoneRoom,
	Audotorium,
	ConcertHall,
	Cave,
	Arena,
	Hangar,
	CarpetedHallway,
	Hallway,
	StoneCorridor,
	Alley,
	Forest,
	City,
	Mountains,
	Quarry,
	Plain,
	ParkingLot,
	SewerPipe,
	Underwater,
	EaxCount,
};

typedef enum _EQ_PRESETS_
{
	Pop = 0,
	Live,
	Club,
	Rock,
	Bass,
	Treble,
	Vocal,
	Powerful,
	Dance,
	Soft,
	Party,
	Classical,
	Jazz,
	EqCount,
}EQ_Presets;

typedef enum _COM_MESSAGE
{
	VistaEQEnable = 0,
	VistaEQLevel = 1,
	VistaDeviceChange = 2,
	VistaVoiceCancelChange = 3,
	VistaKeyChange = 4,
	VistaDefDeviceChange = 5,
	VistaRoomCorrectEnable = 6,
	VistaRoomCorrectDelay = 7,
	VistaRoomCorrectTrim = 8,
	VistaEaxEnable = 9,
	VistaEaxIndex = 10,
	VistaAudioDrvierUnload = 11,
	VISTA_MAX_COM_MESSAGE_COUNT,
}COM_Message;

typedef enum __EndpointFormFactor
{
	RemoteNetworkDevice	= 0,
	Speakers,
	LineLevel,
	Headphones,
	Microphone,
	Headset,
	Handset,
	UnknownDigitalPassthrough,
	SPDIF,
	HDMI,
	UnknownFormFactor,
}_EndpointFormFactor;

