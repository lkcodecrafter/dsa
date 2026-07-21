import java.util.*;

// Facade Pattern
// Intent: Provide a simplified interface to a complex subsystem.

class Amplifier {

    public void on() {
        System.out.println("Amplifier ON");
    }

    public void setVolume(int volume) {
        System.out.println("Amplifier Volume set to " + volume);
    }

    public void off() {
        System.out.println("Amplifier OFF");
    }
}

class DVDPlayer {

    public void on() {
        System.out.println("DVD Player ON");
    }

    public void play(String movieName) {
        System.out.println("Playing movie : " + movieName);
    }

    public void stop() {
        System.out.println("Stopping DVD");
    }

    public void off() {
        System.out.println("DVD Player OFF");
    }
}

class Projector {

    public void on() {
        System.out.println("Projector ON");
    }

    public void wideScreenMode() {
        System.out.println("Projector switched to Wide Screen Mode");
    }

    public void off() {
        System.out.println("Projector OFF");
    }
}

class SoundSystem {

    public void on() {
        System.out.println("Sound System ON");
    }

    public void surroundSound() {
        System.out.println("Surround Sound Enabled");
    }

    public void off() {
        System.out.println("Sound System OFF");
    }
}

/*
 * Facade Class
 * Client communicates only with this class.
 */
class HomeTheaterFacade {

    private Amplifier amplifier;
    private DVDPlayer dvdPlayer;
    private Projector projector;
    private SoundSystem soundSystem;

    public HomeTheaterFacade(
            Amplifier amplifier,
            DVDPlayer dvdPlayer,
            Projector projector,
            SoundSystem soundSystem) {

        this.amplifier = amplifier;
        this.dvdPlayer = dvdPlayer;
        this.projector = projector;
        this.soundSystem = soundSystem;
    }

    public void watchMovie(String movieName) {

        System.out.println("\n======================================");
        System.out.println("Preparing Home Theater...");
        System.out.println("======================================");

        projector.on();
        projector.wideScreenMode();

        amplifier.on();
        amplifier.setVolume(20);

        soundSystem.on();
        soundSystem.surroundSound();

        dvdPlayer.on();
        dvdPlayer.play(movieName);

        System.out.println("Enjoy your movie!");
    }

    public void endMovie() {

        System.out.println("\n======================================");
        System.out.println("Shutting Down Home Theater...");
        System.out.println("======================================");

        dvdPlayer.stop();
        dvdPlayer.off();

        soundSystem.off();

        amplifier.off();

        projector.off();

        System.out.println("Home Theater Shut Down Successfully.");
    }
}

public class FacadePattern {

    public static void main(String[] args) {

        Amplifier amplifier = new Amplifier();
        DVDPlayer dvdPlayer = new DVDPlayer();
        Projector projector = new Projector();
        SoundSystem soundSystem = new SoundSystem();

        HomeTheaterFacade homeTheater = new HomeTheaterFacade(
                amplifier,
                dvdPlayer,
                projector,
                soundSystem);

        homeTheater.watchMovie("Interstellar");

        homeTheater.endMovie();

        homeTheater.watchMovie("Avengers: Endgame");

        homeTheater.endMovie();
    }
}