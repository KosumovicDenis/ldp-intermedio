#ifndef LDP_INTERMEDIO_INCLUDE_LIDARDRIVER_H_
#define LDP_INTERMEDIO_INCLUDE_LIDARDRIVER_H_

#include <ostream>
#include <vector>
#include <cmath>
#include <vector>

class LidarDriver
{
    static constexpr int kBufferDim = 10;
    static constexpr int kFov = 180;
    const double kResolution;

    size_t size_, oldest_scan_idx_;
    std::vector<std::vector<double>> scans_;

public:
    /// \brief Istanzia la classe LidarDriver
    /// \param resolution La risoluzione angolare del sensore in gradi
    explicit LidarDriver(const double resolution = 1);

    /// Accetta uno std::vector<double> contenente una scansione e lo memorizza
    /// nel buffer (sovrascrivendo la scansione meno recente se il buffer è pieno).
    /// Questa funzione esegue anche il controllo di dimensione: se le letture sono
    /// in numero minore del previsto, completa i dati mancanti a 0; se sono in
    /// numero maggiore, li taglia.
    /// \param scan_to_store Dati da memorizzare nel buffer interno
    void new_scan(const std::vector<double> &scan_to_store);

    /// Fornisce la scansione più vecchia e la rimuove dal buffer
    /// \returns La scansione più vecchia del sensore
    std::vector<double> get_scan();

    /// Elimina tutte le scansioni salvate
    void clear_buffer();

    /// Accetta un angolo espresso in gradi e ritorna la lettura corrispondente a
    /// tale angolo nella scansione più recente acquisita dal sensore; tale scansione
    /// non è eliminata dal buffer, e se l’angolo richiesto non è disponibile ritorna
    /// la lettura relativa al valore di angolo più vicino
    /// \param degree L'angolo
    /// \throws BufferEmptyError Se il buffer è vuoto
    /// \throws InvalidDegree Se l'angolo è fuori dal range [0, 180]
    double get_distance(const double degree) const;

    /// Stampa a schermo l'ultima scansione salvata ma non la rimuove dal buffer
    friend std::ostream &operator<<(std::ostream &os, const LidarDriver &l);

    // E' stata tentata un operazione che richiedeva la presenza di elementi nel 
    // buffer quando il buffer era ancora vuoto
    class BufferEmptyError : public std::exception {
        virtual const char* what() const noexcept
        {
            return "[BufferEmptyError] Exception: Buffer is empty!";
        }
    };

    // E' stato immesso un angolo troppo piccolo o grande (minore di 0 oppure 
    // maggiore di 180)
    class InvalidAngle: public std::exception {
        virtual const char* what() const noexcept
        {
            return "[InvalidAngle] Exception: Angle is out of the range [0, 180]";
        }
    };
    // La risoluzione immessa non è tra 0.1° e 1°
    class InvalidResolution: public std::exception {
        virtual const char* what() const noexcept
        {
            return "[InvalidResolution] Exception: Resolution must be in the range [0.1, 1]";
        }
    };
};

#endif // LDP_INTERMEDIO_INCLUDE_LIDARDRIVER_H_