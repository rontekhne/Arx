/* DB TEST */
/* Files involved in database JNI interface
 * All build.gradle and firebase things
 * databaseManager.h, highscores.c, DatabaseManager.Java,
 * DatabaseUsers.Java, SDLActivity.java
 * */
#include "common.h"
#include "databaseManager.h"

JavaVM *jvm;
Users *users;

JNIEXPORT void JNICALL Java_org_libsdl_app_DatabaseManager_getData(JNIEnv *env, jobject thiz, jobjectArray usersArray)
{
    int numUsers = (*env)->GetArrayLength(env, usersArray);

    users = (Users *)malloc(numUsers * sizeof(Users));

    for (int i = 0; i < numUsers; i++) {
        jobject userObject = (*env)->GetObjectArrayElement(env, usersArray, i);

        jmethodID getNameMethod = (*env)->GetMethodID(env, (*env)->GetObjectClass(env, userObject), "getName", "()Ljava/lang/String;");
        jmethodID getScoreMethod = (*env)->GetMethodID(env, (*env)->GetObjectClass(env, userObject), "getScore", "()I");

        jstring name = (jstring)(*env)->CallObjectMethod(env, userObject, getNameMethod);
        jint score = (*env)->CallIntMethod(env, userObject, getScoreMethod);

        const char *cName = (*env)->GetStringUTFChars(env, name, NULL);

        users[i].name = strdup(cName);
        users[i].score = score;

        (*env)->ReleaseStringUTFChars(env, name, cName);
        (*env)->DeleteLocalRef(env, userObject);
    }

    /* Free the users array of structures
     for (int i = 0; i < numUsers; i++) {
            free(users[i].name);
        }
        free(users); */
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
    // Keep a reference on the Java VM.
    jvm = vm;
    return JNI_VERSION_1_4;
}

/* my C function to save data into firebase */
void saveData(JavaVM *jvm, JNIEnv *env, char *name, int score)
{
    (*jvm)->AttachCurrentThread(jvm, &env, NULL);

    jstring jname = (*env)->NewStringUTF(env, name);
    jint jscore = score;

    jclass databaseManagerClass = (*env)->FindClass(env, "org/libsdl/app/DatabaseManager");
    jmethodID callSaveDataMethod = (*env)->GetStaticMethodID(env, databaseManagerClass, "callSaveData", "(Ljava/lang/String;I)V");
    (*env)->CallStaticVoidMethod(env, databaseManagerClass, callSaveDataMethod, jname, jscore);

    (*env)->DeleteLocalRef(env, databaseManagerClass);
    (*env)->DeleteLocalRef(env, jname);
}