#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qchartview.h"
#include <QInputDialog>
#include <QFile>
#include <QMessageBox>
#include "qlabel.h"
#include "filecreator.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Button {
        NaB,    // Not a Button
        RoadMaintenance,
        TrafficMessages,
        TemperatureHistory,
        ObservedWind,
        ObservedCloudiness,
        AverageTemperature,
        MinimumTemperature,
        MaximumTemperature,
        Precipitation,
        OverallRoadCondition,
        TemperatureForecast,
        PredictedWind,
        PredictedTemperature
    };
    Q_ENUM(Button)

    QString preferenceButton_ = "roadmaintenance";
    /**
     * @brief Last active graph name (from upper or lower chart)
     */
    QString placeholdername;
    /**
     * @brief Name of the currently selected preference
     */
    QString preferenceName;
    /**
     * @brief graphtype, currently either line, bar or scatter
     */
    std::string graphtype = "line";

    /**
     * @brief upper chartview
     */
    QChartView* chartview = new QChartView();

    /**
     * @brief lower chartview
     */
    QChartView* chartview2 = new QChartView();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::pair<QDateTime, QDateTime> getTimeRange();

    /**
     * @brief Populates the comparedropdown from saved graphs
     */
    void loadCompareItems();

    /**
     * @brief adds an element to the comparedropdown
     */
    void addtoCompare();

    /**
     * @brief Populates the preferencedropdown from saved preferences
     */
    void loadPreferences();
    Button getCurrentButton();
    std::string getCurrentTask();
    std::string getCurrentMessage();
    std::string getLocation();
    QString getForecast();

public slots:
    /**
     * @brief Receives a signal from the window when the comparedropdown is activated
     * @param index of the selected dropdown option
     */
    void on_CompareDropdown_activated(int index);

    void updateCurrentButton();


private slots:
    void on_graphButton_clicked();

    void on_roadmaintenance_toggled(bool checked);

    void on_trafficmessage_toggled(bool checked);

    void on_saveButton_clicked();

    void on_deleteButton_clicked();

    void on_GraphcomboBox_activated(int index);


    void on_savePreferenceButton_clicked();

    void on_preference_dropdown_activated(int index);

    void on_deletePreferenceButton_clicked();

signals:
    /**
     * @brief sends a signal when the graphButton is Clicked
     */
    void graphButtonClicked();

    /**
     * @brief sends a signal when the saveButton is Clicked
     * @param i is gotten from an inputdialog window which tells if we want to save as an image or as text
     */
    void saveButtonClicked(int i);

    /**
     * @brief sends a signal when the comparedropdown is activated
     */
    void compareDropdownActivated();

    /**
     * @brief sends a signal when the deleteButton is Clicked
     */
    void deleteButtonClicked();

    /**
     * @brief sends a signal when the deletePreferenceButton is Clicked
     */
    void deletePreferenceButtonClicked();

    /**
     * @brief sends a signal when the PreferenceButton is clicked, meaning we want to save the preference
     * @param roaddropdownindex
     * @param grapdropdownindex
     * @param roadmaintenancetypeindex
     * @param forecastdropdownindex
     * @param messagetypedropdownindex
     */
    void PreferenceButtonClicked(int roaddropdownindex, int grapdropdownindex, int roadmaintenancetypeindex, int forecastdropdownindex, int messagetypedropdownindex);

private:
    Ui::MainWindow *ui;

    QLabel* imagelabel = new QLabel();

    Button currentButton_;

    const QStringList forecastIntervals = {"0", "2", "4", "6", "12"};
    const std::vector<std::map<std::string, std::string>> messages = {
        {{"id", "TRAFFIC_ANNOUNCEMENT"}, {"nameEn", "Traffic Announcement"}},
        {{"id", "EXEMPTED_TRANSPORT"}, {"nameEn", "Exempted Transport"}},
        {{"id", "WEIGHT_RESTRICTION"}, {"nameEn", "Weight Restriction"}},
        {{"id", "ROAD_WORK"}, {"nameEn", "Road Work"}}
    };
    const std::vector<std::map<std::string, std::string>> tasks = {
        {
            {"id", ""},     {"nameFi", "Kaikki"},   {"nameEn", "All"},  {"nameSv", "Alla"},     },
        {
            {"id", "BRUSHING"},    {"nameFi", "Harjaus"},    {"nameEn", "Brushing"},    {"nameSv", "Borstning"},  },
        {
            {"id", "BRUSH_CLEARING"},    {"nameFi", "Koneellinen vesakonraivaus"},    {"nameEn", "Brush clearing"},    {"nameSv", "Slyklippning"},  },
        {
            {"id", "CLEANSING_OF_BRIDGES"},    {"nameFi", "Siltojen puhdistus"},    {"nameEn", "Cleansing of bridges"},    {"nameSv", "Rengöring av broar"},  },
        {
            {"id", "CLEANSING_OF_REST_AREAS"},    {"nameFi", "L- ja p-alueiden puhdistus"},    {"nameEn", "Cleansing of rest areas"},    {"nameSv", "Rast- och parkeringsplatsernas rengöring"},  },
        {
            {"id", "CLEANSING_OF_TRAFFIC_SIGNS"},    {"nameFi", "Liikennemerkkien puhdistus"},    {"nameEn", "Cleansing of traffic signs"},    {"nameSv", "Rengöring av trafikmärken"},  },
        {
            {"id", "CLIENTS_QUALITY_CONTROL"},    {"nameFi", "Tilaajan laadunvalvonta"},    {"nameEn", "Clients quality control"},    {"nameSv", "Beställarens kvalitetsövervakning"},  },
        {
            {"id", "COMPACTION_BY_ROLLING"},    {"nameFi", "Jyräys"},    {"nameEn", "Compaction by rolling"},    {"nameSv", "Vibrering"},  },
        {
            {"id", "CRACK_FILLING"},    {"nameFi", "Päällysteiden juotostyöt"},    {"nameEn", "Crack filling"},    {"nameSv", "Fyllning av sprickor i beläggningen"},  },
        {
            {"id", "DITCHING"},    {"nameFi", "Ojitus"},    {"nameEn", "Ditching"},    {"nameSv", "Dikning"},  },
        {
            {"id", "DUST_BINDING_OF_GRAVEL_ROAD_SURFACE"},    {"nameFi", "Sorateiden pölynsidonta"},    {"nameEn", "Dust binding of gravel road surface"},    {"nameSv", "Dammbindning av grusväg"},  },
        {
            {"id", "FILLING_OF_GRAVEL_ROAD_SHOULDERS"},    {"nameFi", "Sorapientareen täyttö"},    {"nameEn", "Filling of gravel road shoulders"},    {"nameSv", "Fyllning av gruskanter"},  },
        {
            {"id", "FILLING_OF_ROAD_SHOULDERS"},    {"nameFi", "Päällystetyn tien sorapientareen täyttö"},    {"nameEn", "Filling of road shoulders"},    {"nameSv", "Belagda vägars kantfyllning"},  },
        {
            {"id", "HEATING"},    {"nameFi", "Kuumennus"},    {"nameEn", "Heating"},    {"nameSv", "Upphettning"},  },
        {
            {"id", "LEVELLING_GRAVEL_ROAD_SURFACE"},    {"nameFi", "Sorateiden tasaus"},    {"nameEn", "Levelling gravel road surface"},    {"nameSv", "Utjämning av grusväg"},  },
        {
            {"id", "LEVELLING_OF_ROAD_SHOULDERS"},    {"nameFi", "Palteen poisto"},    {"nameEn", "Levelling of road shoulders"},    {"nameSv", "Kantskärning"},  },
        {
            {"id", "LEVELLING_OF_ROAD_SURFACE"},    {"nameFi", "Pinnan tasaus"},    {"nameEn", "Levelling of road surface"},    {"nameSv", "Utjämning av vägytan"},  },
        {
            {"id", "LINE_SANDING"},    {"nameFi", "Linjahiekoitus"},    {"nameEn", "Line sanding"},    {"nameSv", "Linjesandning"},  },
        {
            {"id", "LOWERING_OF_SNOWBANKS"},    {"nameFi", "Lumivallien madaltaminen"},    {"nameEn", "Lowering of snowbanks"},    {"nameSv", "Nedsänkning av plogvall"},  },
        {
            {"id", "MAINTENANCE_OF_GUIDE_SIGNS_AND_REFLECTOR_POSTS"},    {"nameFi", "Liikenteen opasteiden ja ohjauslaitteiden hoito sekä reunapaalujen kunnossapito"},    {"nameEn", "Maintenance of guide signs and reflector posts"},    {"nameSv", "Trafikanordningars och kantpålars underhåll"},  },
        {
            {"id", "MECHANICAL_CUT"},    {"nameFi", "Koneellinen niitto"},    {"nameEn", "Mechanical cut"},    {"nameSv", "Mekanisk klippning"},  },
        {
            {"id", "MIXING_OR_STABILIZATION"},    {"nameFi", "Sekoitus tai stabilointi"},    {"nameEn", "Mixing or stabilization"},    {"nameSv", "Blandning och stabilisering"},  },
        {
            {"id", "OTHER"},    {"nameFi", "Muu"},    {"nameEn", "Other"},    {"nameSv", "Annat dylikt"},  },
        {
            {"id", "PATCHING"},    {"nameFi", "Päällysteiden paikkaus"},    {"nameEn", "Patching"},    {"nameSv", "Lappning av beläggning"},  },
        {
            {"id", "PAVING"},    {"nameFi", "Asfaltointi"},    {"nameEn", "Paving"},    {"nameSv", "Asfaltering"},  },
        {
            {"id", "PLOUGHING_AND_SLUSH_REMOVAL"},    {"nameFi", "Auraus ja sohjonpoisto"},    {"nameEn", "Ploughing and slush removal"},    {"nameSv", "Plog- och sörjröjning"},  },
        {
            {"id", "PREVENTING_MELTING_WATER_PROBLEMS"},    {"nameFi", "Sulamisveden haittojen torjunta"},    {"nameEn", "Preventing melting water problems"},    {"nameSv", "Smältvattensbekämpning"},  },
        {
            {"id", "REMOVAL_OF_BULGE_ICE"},    {"nameFi", "Paannejään poisto"},    {"nameEn", "Removal of bulge ice"},    {"nameSv", "Borttagning av svall-is"},  },
        {
            {"id", "RESHAPING_GRAVEL_ROAD_SURFACE"},    {"nameFi", "Sorateiden muokkaushöyläys"},    {"nameEn", "Reshaping gravel road surface"},    {"nameSv", "Grusvägsytans omblandning "},  },
        {
            {"id", "ROAD_INSPECTIONS"},    {"nameFi", "Tiestötarkastus"},    {"nameEn", "Road inspections "},    {"nameSv", "Väggranskning"},  },
        {
            {"id", "ROAD_MARKINGS"},    {"nameFi", "Tiemerkintä"},    {"nameEn", "Road markings"},    {"nameSv", "Vägmarkering"},  },
        {
            {"id", "ROAD_STATE_CHECKING"},    {"nameFi", "Kelintarkastus"},    {"nameEn", "Road state checking"},    {"nameSv", "Väglagsgranskning"},  },
        {
            {"id", "SAFETY_EQUIPMENT"},    {"nameFi", "Turvalaite"},    {"nameEn", "Safety equipment"},    {"nameSv", "Säkerhetsanordning"},  },
        {
            {"id", "SALTING"},    {"nameFi", "Suolaus"},    {"nameEn", "Salting"},    {"nameSv", "Saltning"},  },
        {
            {"id", "SNOW_PLOUGHING_STICKS_AND_SNOW_FENCES"},    {"nameFi", "Aurausviitoitus ja kinostimet"},    {"nameEn", "Snow-ploughing sticks and snow fences"},    {"nameSv", "Plogkäppsmarkering och snödrivor"},  },
        {
            {"id", "SPOT_SANDING"},    {"nameFi", "Pistehiekoitus"},    {"nameEn", "Spot sanding"},    {"nameSv", "Punktsandning"},  },
        {
            {"id", "SPREADING_OF_CRUSH"},    {"nameFi", "Sorastus"},    {"nameEn", "Spreading of crush"},    {"nameSv", "Grusning"},  },
        {
            {"id", "TRANSFER_OF_SNOW"},    {"nameFi", "Lumensiirto"},    {"nameEn", "Transfer of snow"},    {"nameSv", "Bortforsling av snömassor"},  },
        {
            {"id", "UNKNOWN"},    {"nameFi", "Tuntematon"},    {"nameEn", "Unknown"},    {"nameSv", "Obekant"},  }
      };
};
#endif // MAINWINDOW_H
