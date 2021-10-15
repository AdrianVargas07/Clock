
//{{BLOCK(clockFrame)

//======================================================================
//
//	clockFrame, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 24 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 1536 + 2048 = 4096
//
//	Time-stamp: 2020-11-27, 14:37:19
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CLOCKFRAME_H
#define GRIT_CLOCKFRAME_H

#define clockFrameTilesLen 1536
extern const unsigned int clockFrameTiles[384];

#define clockFrameMapLen 2048
extern const unsigned int clockFrameMap[512];

#define clockFramePalLen 512
extern const unsigned int clockFramePal[128];

#endif // GRIT_CLOCKFRAME_H

//}}BLOCK(clockFrame)
