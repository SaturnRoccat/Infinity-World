/**
 * @file  MobSetPreviousRotSystem.hpp
 *
 */
#pragma once
#define AUTO_GENERATED
#include "llapi/Global.h"

#define BEFORE_EXTRA

#undef BEFORE_EXTRA

/**
 * @brief MC class MobSetPreviousRotSystem.
 *
 */
class MobSetPreviousRotSystem {

#define AFTER_EXTRA

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_MOBSETPREVIOUSROTSYSTEM
public:
    class MobSetPreviousRotSystem& operator=(class MobSetPreviousRotSystem const &) = delete;
    MobSetPreviousRotSystem(class MobSetPreviousRotSystem const &) = delete;
    MobSetPreviousRotSystem() = delete;
#endif

public:
    /**
     * @symbol ?createSystem\@MobSetPreviousRotSystem\@\@SA?AUTickingSystemWithInfo\@\@XZ
     */
    MCAPI static struct TickingSystemWithInfo createSystem();
    /**
     * @symbol ?tick\@MobSetPreviousRotSystem\@\@SAXV?$ViewT\@VStrictEntityContext\@\@VEntityRegistryBase\@\@U?$Include\@V?$FlagComponent\@UActorMovementTickNeededFlag\@\@\@\@V?$FlagComponent\@UMobFlag\@\@\@\@\@\@UActorHeadRotationComponent\@\@UActorRotationComponent\@\@UMobBodyRotationComponent\@\@\@\@\@Z
     */
    MCAPI static void tick(class ViewT<class StrictEntityContext, class EntityRegistryBase, struct Include<class FlagComponent<struct ActorMovementTickNeededFlag>, class FlagComponent<struct MobFlag>>, struct ActorHeadRotationComponent, struct ActorRotationComponent, struct MobBodyRotationComponent>);

//private:
    /**
     * @symbol ?_setPreviousRotation\@MobSetPreviousRotSystem\@\@CAXAEAVStrictEntityContext\@\@AEAUActorHeadRotationComponent\@\@AEAUActorRotationComponent\@\@AEAUMobBodyRotationComponent\@\@\@Z
     */
    MCAPI static void _setPreviousRotation(class StrictEntityContext &, struct ActorHeadRotationComponent &, struct ActorRotationComponent &, struct MobBodyRotationComponent &);

private:

};
