using namespace std;
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include "imdb.h"

const char *const imdb::kActorFileName = "actordata";
const char *const imdb::kMovieFileName = "moviedata";

typedef struct{
  string name;
  const void* file;
} actorStruct;
typedef struct{
  film movie;
  const void* file;
} filmStruct;

imdb::imdb(const string& directory)
{
  const string actorFileName = directory + "/" + kActorFileName;
  const string movieFileName = directory + "/" + kMovieFileName;
  
  actorFile = acquireFileMap(actorFileName, actorInfo);
  movieFile = acquireFileMap(movieFileName, movieInfo);
}

bool imdb::good() const
{
  return !( (actorInfo.fd == -1) || 
	    (movieInfo.fd == -1) ); 
}
int cmpFilms(const void * target, const void * a){
  filmStruct* targetStruct = (filmStruct*)target;
  film targetName = targetStruct->movie;
  const void* movieFile = targetStruct->file;
  film aName;
  int aOffset = *(int*)a;
  aName.title = (char*)movieFile + aOffset;
  char charX = *((char*)movieFile + aOffset + aName.title.length() + 1);
  int x = (int)charX;
  aName.year = 1900 + x;
  if(targetName == aName)
    return 0;
  if(targetName < aName)
    return -1;
  return 1;
}
int cmpActors(const void * target, const void * a){
  actorStruct* targetStruct = (actorStruct*)target;
  string targetName = targetStruct->name;
  const void* actorFile = targetStruct->file;
  int aOffset = *(int*)a;
  string aName = (char*)actorFile + aOffset;
  return strcmp(targetName.c_str() , aName.c_str());
}
// you should be implementing these two methods right here... 
bool imdb::getCredits(const string& player, vector<film>& films) const {
  int n = *(int*)actorFile;
  actorStruct playerStruct;
  playerStruct.name = player;
  playerStruct.file = actorFile;
  void* playerPTR = bsearch(&playerStruct, (int*)actorFile + 1, n, sizeof(int), cmpActors);
  if(playerPTR == NULL)
    return false;
  int offset = *(int*)playerPTR;
  playerPTR = (char*)actorFile + offset;
  int nameLength = (player.length() / 2 + 1) * 2;
  short nShort = *(short*)((char*)playerPTR + nameLength);
  nameLength = nameLength / 4 + 1;
  playerPTR = (int*)playerPTR + nameLength;
  for(short i = 0; i < nShort; i++){
    film movie;
    int movieOffset = *(int*)playerPTR;
    string movieTitle = (char*)movieFile + movieOffset;
    movie.title = movieTitle;
    movieOffset += movieTitle.length() + 1;
    int x =*((char*)movieFile + movieOffset);
    movie.year = 1900 + x;
    films.push_back(movie);
    playerPTR = (int*)playerPTR + 1;
  }
  return true;
}
bool imdb::getCast(const film& movie, vector<string>& players) const {
  int n = *(int*)movieFile;
  filmStruct movieStruct;
  movieStruct.movie = movie;
  movieStruct.file = movieFile;
  //cout << "ver gavcdi" << endl;
  void* moviePTR = bsearch(&movieStruct, (int*)movieFile + 1, n, sizeof(int), cmpFilms);
  if(moviePTR == NULL)
    return false;
  int offset = *(int*)moviePTR;
  moviePTR = (char*)movieFile + offset;
  int nameLength = movie.title.length() + 1;
  nameLength = (nameLength / 2 + 1) * 2;
  short nShort = *(short*)((char*)moviePTR + nameLength);
  nameLength = nameLength / 4 + 1;
  moviePTR = (int*)moviePTR + nameLength;
  for(short i = 0; i < nShort; i++){
    int playerOffset = *(int*)moviePTR;
    string player = (char*)actorFile + playerOffset;
    players.push_back(player);
    moviePTR = (int*)moviePTR + 1;
  }
 return true;
}
imdb::~imdb()
{
  releaseFileMap(actorInfo);
  releaseFileMap(movieInfo);
}

// ignore everything below... it's all UNIXy stuff in place to make a file look like
// an array of bytes in RAM.. 
const void *imdb::acquireFileMap(const string& fileName, struct fileInfo& info)
{
  struct stat stats;
  stat(fileName.c_str(), &stats);
  info.fileSize = stats.st_size;
  info.fd = open(fileName.c_str(), O_RDONLY);
  return info.fileMap = mmap(0, info.fileSize, PROT_READ, MAP_SHARED, info.fd, 0);
}

void imdb::releaseFileMap(struct fileInfo& info)
{
  if (info.fileMap != NULL) munmap((char *) info.fileMap, info.fileSize);
  if (info.fd != -1) close(info.fd);
}
