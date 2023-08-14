package org.libsdl.app;

import android.util.Log;

import androidx.annotation.NonNull;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class DatabaseManager {
    static {
        System.loadLibrary("main");
    }

    private static DatabaseManager instance;

    public static void initializeInstance() {
        instance = new DatabaseManager();
    }

    public static DatabaseManager getInstance() {
        return instance;
    }

    public native void getData(DatabaseUsers[] users);
    public void saveData(String name, int score) {
        DatabaseReference usersRef = FirebaseDatabase.getInstance().getReference("users");
        usersRef.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                long numberOfChildren = dataSnapshot.getChildrenCount();
                DatabaseReference newUserRef = usersRef.child(String.valueOf(numberOfChildren));
                newUserRef.child("name").setValue(name);
                newUserRef.child("score").setValue(score);
            }
            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {
                Log.e("Arx", "Error: " + databaseError.getMessage());
            }
        });
    }
    public static void callSaveData(String name, int score) {
        if (instance != null) {
            instance.saveData(name, score);
        }
    }
}
