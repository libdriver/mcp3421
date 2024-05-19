[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MCP3421

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mcp3421/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der MCP3421 ist ein einkanaliger, rauscharmer, hochpräziser ΔΣ-A/D-Wandler mit Differenzeingängen und bis zu 18 Bit Auflösung in einem kleinen SOT-23-6-Gehäuse. Die integrierte Präzisionsreferenzspannung von 2,048 V ermöglicht einen Eingangsbereich von ±2,048 V differenziell (Δ Spannung = 4,096 V). Das Gerät verwendet eine zweiadrige I2C-kompatible serielle Schnittstelle und wird mit einer einzelnen Stromversorgung von 2,7 V bis 5,5 V betrieben. Das MCP3421-Gerät führt die Konvertierung je nach Benutzer mit Raten von 3,75, 15, 60 oder 240 Samples pro Sekunde (SPS) durch steuerbare Konfigurationsbiteinstellungen über die zweiadrige serielle I2C-Schnittstelle. Dieses Gerät verfügt über einen integrierten programmierbaren Verstärkungsverstärker (PGA). Der Benutzer kann die PGA-Verstärkung von x1, x2, x4 oder x8 auswählen, bevor die Analog-Digital-Wandlung stattfindet. Dadurch kann das MCP3421-Gerät ein kleineres Eingangssignal mit hoher Auflösung umwandeln. Das Gerät verfügt über zwei Konvertierungsmodi: (a) Kontinuierlicher Modus und (b) One-Shot-Modus. Im One-Shot-Modus wechselt das Gerät nach einer Konvertierung automatisch in einen Standby-Modus mit geringem Stromverbrauch. Dies reduziert den Stromverbrauch während Leerlaufzeiten erheblich. Das MCP3421-Gerät kann für verschiedene hochpräzise Analog-Digital-Datenumwandlungsanwendungen verwendet werden, bei denen Designeinfachheit, geringer Stromverbrauch und geringer Platzbedarf im Vordergrund stehen.

LibDriver MCP3421 ist der von LibDriver gestartete Vollfunktionstreiber von MCP3421. LibDriver MCP3421 bietet ADC-Konvertierung im kontinuierlichen Modus, ADC-Konvertierung im Einzelmodus und andere Funktionen. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver MCP3421-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver MCP3421 IIC.

/test enthält den Testcode des LibDriver MCP3421-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver MCP3421-Beispielcode.

/doc enthält das LibDriver MCP3421-Offlinedokument.

/Datenblatt enthält MCP3421-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

```C
#include "driver_mcp3421_basic.h"

uint8_t res;
uint32_t i;
double s;

/* basic init */
res = mcp3421_basic_init();
if (res != 0)
{
    mcp3421_interface_debug_print("mcp3421: basic init failed.\n");

    return 1;
}

...
    
for (i = 0; i < 3; i++)
{
    /* read the data */
    res = mcp3421_basic_read((double *)&s);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: basic read failed.\n");
        (void)mcp3421_basic_deinit();

        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: %d/%d.\n", i + 1, 3);
    mcp3421_interface_debug_print("mcp3421: adc is %0.4fV.\n", s);
    mcp3421_interface_delay_ms(1000);
    
    ...
}

...
    
(void)mcp3421_basic_deinit();

return 0;
```
#### example shot

```C
#include "driver_mcp3421_shot.h"

uint8_t res;
uint32_t i;
double s;

/* shot init */
res = mcp3421_shot_init();
if (res != 0)
{
    mcp3421_interface_debug_print("mcp3421: basic init failed.\n");

    return 1;
}

...
    
for (i = 0; i < 3; i++)
{
    /* read the data */
    res = mcp3421_shot_read((double *)&s);
    if (res != 0)
    {
        mcp3421_interface_debug_print("mcp3421: basic read failed.\n");
        (void)mcp3421_shot_deinit();

        return 1;
    }
    mcp3421_interface_debug_print("mcp3421: %d/%d.\n", i + 1, 3);
    mcp3421_interface_debug_print("mcp3421: adc is %0.4fV.\n", s);
    mcp3421_interface_delay_ms(1000);
    
    ...
}

...
    
(void)mcp3421_shot_deinit();

return 0;
```

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/mcp3421/index.html](https://www.libdriver.com/docs/mcp3421/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.