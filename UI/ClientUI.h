#ifndef _ClientUI_h_
#define _ClientUI_h_

#include <boost/filesystem/path.hpp>
#include <GG/GGFwd.h>

#include "../universe/EnumsFwd.h"
#include "../universe/TemporaryPtr.h"
#include "../util/Random.h"

#include <map>

class Fleet;
class IntroScreen;
class MapWnd;
class MessageWnd;
class PlayerListWnd;
class MultiPlayerLobbyWnd;
struct SaveGameUIData;
class System;


//! \brief ClientUI Main Module
//!This is the main class of the ClientUI module.
//!it contains objects of many other classes and controls the
//!display of all information onscreen.
class ClientUI {
public:
    //! \name Structors //!@{
    ClientUI();
    ~ClientUI();
    //!@}

    //! \name Accessors //!@{
    MapWnd*                 GetMapWnd();                                //!< Returns the main map window.
    MapWnd const*           GetMapWndConst() const;                     //!< Returns the main map window.
    MessageWnd*             GetMessageWnd();                            //!< Returns the chat / message window.
    PlayerListWnd*          GetPlayerListWnd();                         //!< Returns the players list window.
    IntroScreen*            GetIntroScreen();                           //!< Returns the intro screen / splash window.
    MultiPlayerLobbyWnd*    GetMultiPlayerLobbyWnd();                   //!< Returns the multiplayer lobby window.

    void    GetSaveGameUIData(SaveGameUIData& data) const;              //!< populates the relevant UI state that should be restored after a save-and-load cycle
    //!@}

    //! \name Mutators //!@{
    /** Return the IntroScreen. Hides the MapWnd, MessageWnd and
        PlayerListWnd if visible, but doesn't create them just to hide them.
     **/
    void    ShowIntroScreen();
    void    InitTurn(int turn_number);                                  //!< resets all active controls to use the latest data when it has been changed at the beginning of a new turn
    void    RestoreFromSaveData(const SaveGameUIData& elem);            //!< restores the UI state that was saved in an earlier call to GetSaveGameUIData().

    bool    ZoomToObject(const std::string& name);
    bool    ZoomToObject(int id);
    bool    ZoomToPlanet(int id);                                       //!< Zooms to a particular planet on the galaxy map and opens the sidepanel to show it, or if production screen is open selects it
    bool    ZoomToPlanetPedia(int id);                                  //!< Opens the encyclodedia window and presents the entry for the given planet
    bool    ZoomToSystem(int id);                                       //!< Zooms to a particular system on the galaxy map and opens the sidepanel to show it
    bool    ZoomToFleet(int id);                                        //!< Zooms to a particular fleet on the galaxy map and opens the fleet window
    bool    ZoomToShip(int id);                                         //!< Zooms to a particular ship on the galaxy map and opens its fleet and/or ship window
    bool    ZoomToBuilding(int id);                                     //!< Zooms to a particular building on the galaxy map and opens the sidepanel to show it
    bool    ZoomToField(int id);                                        //!< Zooms to a particular field on the map
    bool    ZoomToCombatLog(int id);                                    //!< Opens combat log for indicated combat

    void    ZoomToSystem(TemporaryPtr<const System> system);            //!< Zooms to a particular system on the galaxy map
    void    ZoomToFleet(TemporaryPtr<const Fleet> fleet);               //!< Zooms to a particular fleet on the galaxy map and opens the fleet window

    bool    ZoomToContent(const std::string& name, bool reverse_lookup = false);
    bool    ZoomToTech(const std::string& tech_name);                  //!< Opens the technology screen and presents a description of the given technology
    bool    ZoomToBuildingType(const std::string& building_type_name); //!< Opens the production screen and presents a description of the given building type
    bool    ZoomToSpecial(const std::string& special_name);            //!< Opens the ??? screen and presents a description of the given special
    bool    ZoomToShipHull(const std::string& hull_name);              //!< Opens the design screen and presents a description of the given hull type
    bool    ZoomToShipPart(const std::string& part_name);              //!< Opens the design screen and presents a description of the given part type
    bool    ZoomToSpecies(const std::string& species_name);            //!< Opens the ??? screen and presents a description of the given species
    bool    ZoomToFieldType(const std::string& field_type_name);       //!< Opens the ??? screen and presents a description of the given field type

    bool    ZoomToShipDesign(int design_id);                           //!< Opens the design screen and presents a description of the given ship design
    bool    ZoomToEmpire(int empire_id);                               //!< Opens the ??? screen and presents a description of the given empire
    bool    ZoomToMeterTypeArticle(const std::string& meter_string);   //!< Opens the encyclopedia and presents the entry for MeterType @a meter_type

    bool    ZoomToEncyclopediaEntry(const std::string& str);           //!< Opens the encyclodedia window and presents the entry for the given term

    void    DumpObject(int object_id);                                 //!< Displays debug info about specified object in messages window

    void    InitializeWindows();

    /** Loads a texture at random from the set of files starting with \a prefix in directory \a dir. */
    boost::shared_ptr<GG::Texture> GetRandomTexture(const boost::filesystem::path& dir, const std::string& prefix, bool mipmap = false);

    /** Loads texture \a n % N from the set of files starting with \a prefix in directory \a dir, where N is the number
        of files found in \a dir with prefix \a prefix. */
    boost::shared_ptr<GG::Texture> GetModuloTexture(const boost::filesystem::path& dir, const std::string& prefix, int n, bool mipmap = false);

    /** Returns all textures in the set of files starting with \a prefix in directory \a dir. */
    std::vector<boost::shared_ptr<GG::Texture> > GetPrefixedTextures(const boost::filesystem::path& dir, const std::string& prefix, bool mipmap = false);
    //!@}

    static ClientUI* GetClientUI();     //!< returns a pointer to the singleton ClientUI class

    /** Shows a message dialog box with the given message; if
      * \a play_alert_sound is true, and UI sound effects are currently enabled,
      * the default alert sound will be played as the message box opens */
    static void MessageBox(const std::string& message, bool play_alert_sound = false);

    /** Loads the requested texture from file \a name; mipmap textures are
      * generated if \a mipmap is true; loads default missing.png if name isn't
      * found. */
    static boost::shared_ptr<GG::Texture> GetTexture(const boost::filesystem::path& path, bool mipmap = false);

    /** Returns the default font in the specified point size.  Uses "UI.font"
      * option setting as the font filename, and provides Unicode character sets
      * based on the contents of the stringtable in use. */
    static boost::shared_ptr<GG::Font> GetFont(int pts = Pts());

    /** Returns the default font in the specified point size.  Uses
      * "UI.font-bold" option setting as the font filename, and provides
      * Unicode character sets based on the contents of the stringtable in use. */
    static boost::shared_ptr<GG::Font> GetBoldFont(int pts = Pts());

    /** Returns the default font in the specified point size.  Uses
      * "UI.title-font" option setting as the font filename, and provides
      * Unicode character sets based on the contents of the stringtable in use. */
    static boost::shared_ptr<GG::Font> GetTitleFont(int pts = TitlePts());

    //!@{
    static boost::filesystem::path ArtDir();    //!< directory holding artwork
    static boost::filesystem::path SoundDir();  //!< directory holding sound and music

    static int          Pts();                  //!< default point size
    static int          TitlePts();             //!< default point size to use for window title

    static GG::Clr      TextColor();            //!< color of UI text
    static GG::Clr      DefaultLinkColor();     //!< default color of UI links
    static GG::Clr      RolloverLinkColor();    //!< rollover color of UI links

    // generic UI windows
    static GG::Clr      WndColor();             //!< background color of a UI window
    static GG::Clr      WndOuterBorderColor();  //!< color of the outermost border
    static GG::Clr      WndInnerBorderColor();  //!< color of the innermost border

    // controls
    static GG::Clr      CtrlColor();            //!< background color of UI controls
    static GG::Clr      CtrlBorderColor();
    static GG::Clr      ButtonHiliteColor();
    static GG::Clr      ButtonHiliteBorderColor();

    static int          ScrollWidth();

    static GG::Clr      DropDownListArrowColor();

    static GG::Clr      EditHiliteColor();

    static GG::Clr      StatIncrColor();        //!< used to color increasing stats text (eg "+2")
    static GG::Clr      StatDecrColor();        //!< used to color decreasing stats text (eg "-3")

    static GG::Clr      StateButtonColor();     //!< colour of selected state button markers

    static int          SystemIconSize();                   //!< the width/height of a System/Icon at zoom = 1.0
    static int          SystemTinyIconSizeThreshold();      //!< the width/height of a system icon below which the tiny system icons should be used
    static int          SystemCircleSize();                 //!< the width/height of the system-enclosing circle
    static int          SystemSelectionIndicatorSize();     //!< the width/height of a system selection indicator
    static int          SystemSelectionIndicatorRPM();      //!< revolutions per minute to rotate system selection indicator

    static GG::Clr      SystemNameTextColor();              //!< the colour of system names that aren't owned by any player (as far as this client knows)

    static double       TinyFleetButtonZoomThreshold();     //!< the minimum zoom level of the map at which to show tiny (any) fleet icons
    static double       SmallFleetButtonZoomThreshold();    //!< the minimum zoom level of the map at which to show small fleet icons
    static double       MediumFleetButtonZoomThreshold();   //!< the minimum zoom level of the map at which to show medium fleet icons

    // Content Texture Getters
    static boost::shared_ptr<GG::Texture>   PlanetIcon(PlanetType planet_type);
    static boost::shared_ptr<GG::Texture>   PlanetSizeIcon(PlanetSize planet_size);
    static boost::shared_ptr<GG::Texture>   MeterIcon(MeterType meter_type);
    static boost::shared_ptr<GG::Texture>   BuildingIcon(const std::string& building_type_name);
    static boost::shared_ptr<GG::Texture>   CategoryIcon(const std::string& category_name);
    static boost::shared_ptr<GG::Texture>   TechIcon(const std::string& tech_name);
    static boost::shared_ptr<GG::Texture>   SpecialIcon(const std::string& special_name);
    static boost::shared_ptr<GG::Texture>   SpeciesIcon(const std::string& species_name);
    static boost::shared_ptr<GG::Texture>   FieldTexture(const std::string& field_type_name);
    static boost::shared_ptr<GG::Texture>   PartIcon(const std::string& part_name);
    static boost::shared_ptr<GG::Texture>   HullTexture(const std::string& hull_name);
    static boost::shared_ptr<GG::Texture>   HullIcon(const std::string& hull_name);
    static boost::shared_ptr<GG::Texture>   ShipDesignIcon(int design_id);

    // research screen
    static GG::Clr      KnownTechFillColor();
    static GG::Clr      KnownTechTextAndBorderColor();
    static GG::Clr      ResearchableTechFillColor();
    static GG::Clr      ResearchableTechTextAndBorderColor();
    static GG::Clr      UnresearchableTechFillColor();
    static GG::Clr      UnresearchableTechTextAndBorderColor();
    static GG::Clr      TechWndProgressBarBackgroundColor();
    static GG::Clr      TechWndProgressBarColor();

    static GG::Clr      CategoryColor(const std::string& category_name);

    static std::map<PlanetType, std::string>& PlanetTypeFilePrefixes();
    static std::map<StarType, std::string>&   StarTypeFilePrefixes();
    static std::map<StarType, std::string>&   HaloStarTypeFilePrefixes();
    //!@}

private:
    typedef std::pair<std::vector<boost::shared_ptr<GG::Texture> >,
                      boost::shared_ptr<SmallIntDistType> >         TexturesAndDist;

    typedef std::map<std::string, TexturesAndDist>                  PrefixedTextures;

    TexturesAndDist     PrefixedTexturesAndDist(const boost::filesystem::path& dir,
                                                const std::string& prefix,
                                                bool mipmap);

    void                HandleSizeChange(bool fullscreen) const;
    void                HandleFullscreenSwitch() const;

    mutable MapWnd*         m_map_wnd;              //!< the galaxy map
    MessageWnd*             m_message_wnd;          //!< the messages / chat display
    PlayerListWnd*          m_player_list_wnd;      //!< the players list
    IntroScreen*            m_intro_screen;         //!< splash screen / main menu when starting program
    MultiPlayerLobbyWnd*    m_multiplayer_lobby_wnd;//!< the multiplayer lobby

    PrefixedTextures    m_prefixed_textures;

    static ClientUI*    s_the_UI;           //!< pointer to the one and only ClientUI object
};

/** This exists as a way of allowing UI colors to be specified on the command
  * line with one option and "(r,g,b,a)", instead of one option per color
  * channel.  GG::Clr is not streamable using the normal means, due to what
  * appears to be a bug in MSVC 7.1. */
struct StreamableColor {
    StreamableColor();
    StreamableColor(const GG::Clr& clr);
    GG::Clr ToClr() const;
    int r, g, b, a;
};
std::ostream& operator<<(std::ostream& os, const StreamableColor& clr);
std::istream& operator>>(std::istream& is, StreamableColor& clr);

/** Increases the given value when font size is larger than 12 */
int FontBasedUpscale(int x);

#endif // _ClientUI_h_
