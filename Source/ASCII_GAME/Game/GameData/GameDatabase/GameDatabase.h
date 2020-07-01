#ifndef GAME_DATABASE_h
#define GAME_DATABASE_h

class C_GameDatabase
{
public:
    static C_GameDatabase* Instance();

    bool Init(void);
   
private:
    C_GameDatabase();

    static C_GameDatabase* m_pInstance;
	
};

void InitialiseTagFromBinary(const char** pStr, char*& buffer);

#endif
