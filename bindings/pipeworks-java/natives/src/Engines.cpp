
#include <engine.hpp>
#include <jni.h>

#include <array>
#include <cstdint>

static_assert(sizeof(std::uintptr_t)<=sizeof(jlong));

JNICALL void Engine_close(JNIEnv* env,jobject o) noexcept {
    jclass cl = env->GetObjectClass(o);
    jfieldID f = env->GetFieldID(cl,"ptr_mengine","J");
    auto i =env->GetLongField(o,f);
    auto* e = reinterpret_cast<pipeworks::Engine*>(static_cast<std::uintptr_t>(i));
    delete e;
}

JNICALL jlong Engine_init_native(JNIEnv* env,jclass cl,jobject nr)noexcept{
    jclass nrc = env->GetObjectClass(nr);
    jfieldID f = env->GetFieldID(cl,"field","J");
    auto i = env->GetLongField(nr,f);
    env->SetLongField(nr,f,0);
    // The above is a take operation.
    // If anything goes wrong, we leak i, but that's better than DF.
    auto* e = new pipeworks::Engine{std::unique_ptr<pipeworks::Renderer>{reinterpret_cast<pipeworks::Renderer*>(static_cast<std::uintptr_t>(i))}};
    return static_cast<jlong>(reinterpret_cast<std::uintptr_t>(e));
}


static const JNINativeMethod methods[] = {
    // It will be fine. There will be zero issues...
    {const_cast<char*>("close0"),const_cast<char*>("()V"),reinterpret_cast<void*>(Engine_close)},
    {const_cast<char*>("engine_init1"),const_cast<char*>("(Lgithub/lightningcreations/pipeworks/java/NativeRenderer;)J"),reinterpret_cast<void*>(Engine_init_native)}
};



extern"C"{
    JNIEXPORT JNICALL void Java_github_lightningcreations_pipeworks_java_Engine_registerNatives(JNIEnv* env,jclass cl){
        env->RegisterNatives(cl, methods, std::size(methods));
    }
}
