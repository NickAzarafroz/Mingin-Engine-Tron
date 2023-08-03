#include "ServiceLocator.h"
namespace dae
{
    std::unique_ptr<SoundSystem> ServiceLocator::m_pSS_Instance{ std::make_unique<NullSoundSystem>() };
}