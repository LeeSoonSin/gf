#include "Game.h"
#include "SDL_image.h"

bool Game::init(const char *title, int xpos, int ypos, int width, int height, int flags)
{
  if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(m_pWindow != 0)
    {
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
      if(m_pRenderer != 0)
      {
        SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
      }
      else
      {
        return false; // 랜더러 생성 실패
      }
      SDL_Surface* pTempSurface = IMG_Load("Assets/animate-alpha.png");
      //SDL_Surface* pTempSurface = IMG_Load("Assets/animate-alpha.png");
      if(pTempSurface != 0)
      {
      m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
      SDL_FreeSurface(pTempSurface);

      m_sourceRectangle.w = 128;
      m_sourceRectangle.h = 82;
      //m_sourceRectangle.w =32;   //낙타 얼굴
      //m_sourceRectangle.h = 41;  //낙타 얼굴
      //m_sourceRectangle.w =640;  //화면 전체에 나타남.
      //m_sourceRectangle.h = 300; //화면 전체에 나타남.
      m_destinationRectangle.w = m_sourceRectangle.w;
      m_destinationRectangle.h = m_sourceRectangle.h;
      
      m_destinationRectangle.x = 220;
      m_destinationRectangle.y = 100;
      //m_destinationRectangle.x = m_sourceRectangle.x = 41;
      //m_destinationRectangle.y = m_sourceRectangle.y = 41;
      //m_destinationRectangle.x = 41;
      //m_destinationRectangle.y = 41;
      }
    }
    else
      {
        return false; // 윈도우 생성 실패
      }
  }
  else
      {
        return false; // SDL 초기화 실패
      }
  m_bRunning = true;
  return true;
}

void Game::update()
{
  m_sourceRectangle.x = 128 * ((SDL_GetTicks() / 80) % 6);
  m_destinationRectangle.x = ((SDL_GetTicks() / 10) % 600);
  /*if(m_destinationRectangle.x > 450)
  {
    m_destinationRectangle.x = 0;
  }*/
  /*if(m_destinationRectangle.x > 450)
  {
    SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 0, 0, SDL_FLIP_HORIZONTAL);
  }
  else if(m_destinationRectangle.x < 0)
  {
    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
  }
  else
  {
    SDL_Quit();
  }*/ 
}
void Game::render()
{
  SDL_RenderClear(m_pRenderer);
  SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
  SDL_RenderPresent(m_pRenderer);
}
bool Game::running()
{
  return m_bRunning;
}
void Game::handleEvents()
{
  SDL_Event event;
  if(SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
        m_bRunning = false;
        break;

        default:
        break;
    }
  }
}

void Game::clean()
{
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}