# Smoke Sensor Zigbee Telink TLSR8258 (E-BYTE E180-Z5812SP)

[Repository smoke_sensor_zed](https://github.com/slacky1965/smoke_sensor_zed)


* [Описание](#description)
* [Железо](#hardware)
* [Софт](#software)  
* [Принцип работы](#firmware)
* [Настройка](#settings)
* [Home Assistant](#home_assistant)
* [Alisa](#alisa)

---

## <a id="description">Описание</a>

* Сделано в виде дополнительной платы к заводскому пожарному дымовому извещателю [Рубеж ИП 212-50М2](https://yandex.ru/search?text=%D0%A0%D1%83%D0%B1%D0%B5%D0%B6+%D0%98%D0%9F+212-50%D0%9C2&lr=213).
* Изменяет статус ALARM1 в IAS при обнаружении дыма.
* Изменяет статус TAMPER в IAS при снятии извещателя с крепежной пластины.
* Посылает команду On-Off (Off-On или Toggle, в зависимости от выбранных настроек) при обнаружении дыма.
* Сохраняет настройки в энергонезависимой памяти модуля.
* Передает показания по сети Zigbee.
* Кластер On_Off имеет возможность напрямую подключаться к исполнительному устройству минуя координатор.
* Взаимодейстивие с "умными домами" через zigbee2mqtt.
* Первоначальная настройка происходит через web-интерфейс zigbee2mqtt.
* Подключиться к сети zigbee - удерживать кнопку на плате устройства более 5 секунд.
* Покинуть сеть zigbee - удерживать кнопку на плате устройства более 5 секунд.
* Сделать restart модуля - нажать кнопку 5 раз.
* При одиночном нажатии кнопки модуль просыпается и высылает отчеты.

---

## <a id="hardware">Железо</a>

В проекте используется модуль от компании E-BYTE на чипе TLSR8258F512ET32 - E180-Z5812SP.

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/E180-Z5812SP.jpg" alt="E-BYTE E180-Z5812SP"/>

Испытывалось все на вот такой плате совместной разработки (спасибо [Олегу](https://t.me/Novgorod73))

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/tlsr8258_devkit_zi.png" alt="TLSR8258 devkit_zi"/>

---

**Схема**

Схема изделия.

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/Schematic_Smoke_Sensor_TLSR8258.jpg"/>

**Плата**

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/board_top_empty.png"/>

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/board_bottom_empty.png"/>

На гребенку выведены следующие пины модуля

* SWS, GND - для заливки в модуль прошивки
* TXD-DBG - на всякий случай, вдруг кому-то пригодится для отладки.

[Ссылки на проект в easyeda](https://oshwlab.com/slacky/smoke_sensor_tlsr8258)

Детали, напечатанные на 3D принтере.

[Прокладка для платы](https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/3D/Pad.STL)

[Кронштейн платы](https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/3D/Support_new.STL)

Плата zigbee подключается к заводскому модулю следующим образом - 

* Красный провод (1 контакт разъема CN1) - к +9v - контакт 1 на плате извещателя.
* Черный провод (2 контакт разъема CN1) - к -9v (или земля) - контакт 2 на плате извещателя.
* Желтый провод (3 контакт раъема CN1) - контакт К1 на плате извещателя.

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/rubej_k1.jpg"/>


**Готовое устройство**

Плата интегрированна в заводской пожарный дымовой извещатель Рубеж ИП 212-50М2.

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/device1.jpg"/>

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/device2.jpg"/>

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/device3.jpg"/>

---

## <a id="software">Софт</a>

Прошивок две. Изначально предполагалось, что микропереключатель на TAMPER будет нормально замкнутым. Но, что-то с ними проблема. И даже в лоте на Али, на котором указано, что это NC, китаец прислал NO. Потому прошивок две - одна под выключатель TAMPER NC, вторая под NO.

Нужную прошивку из [репозитория](https://github.com/slacky1965/smoke_sensor_zed) нужно залить в модуль с помощью [github.com/pvvx/TLSRPGM](https://github.com/pvvx/TLSRPGM) или оригинального программатора от Telink.

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/telink_pgm.jpg" alt="Telink PGM"/>

Как сделать недорогой программатор на базе модулей TB-03 или TB-04 можно почитать [тут](https://slacky1965.github.io/electricity_meter_zrd/#%D0%B7%D0%B0%D0%B3%D1%80%D1%83%D0%B7%D0%BA%D0%B0-%D0%BF%D1%80%D0%BE%D1%88%D0%B8%D0%B2%D0%BA%D0%B8)

Используется последнее [SDK zigbee](http://wiki.telink-semi.cn/tools_and_sdk/Zigbee/Zigbee_SDK.zip) от Telink'а. Проект сформирован таким образом, что его можно собрать обычным make'ом как под Windows, в оболочке [Git Bash](https://git-scm.com/download/win), а также под Linux'ом (я проверял на Debian 11).

Как добавить проект в Eclipse можно почитать [тут](https://slacky1965.github.io/electricity_meter_zrd/#%D0%BA%D0%BE%D0%BC%D0%BF%D0%B8%D0%BB%D1%8F%D1%86%D0%B8%D1%8F). Все точно так же, только для другого проекта.

Прошивка собрана по схеме, т.е. подключается файл платы `board_8258_diy.h`. Еще адаптирована плата devkit_zi. Для других вариантов придется самостоятельно редактировать файл нужной платы.

---

## <a id="firmware">Описание работы модуля</a>

В первый старт происходит попытка подключения к сети Zigbee. Если попытка удалась, модуль переходит в штатный режим работы. 

**Polling**
	
Первые 30 секунд модуль просыпается раз в 3 секунды. По истечению 30 секунд модуль засыпает на 5 минут. Через 5 минут опять просыпается раз в 3 секунды последующие 30 секунд. И опять засыпает на 5 минут. И так по кругу. Можно было сделать просыпание модуля раз в 5 минут, но zigbee2mqtt по умолчанию проверяет устройства на наличие в сети примерно раз в 10 минут. И начинает ругаться в логе, что устройство не найдено и выставляет статус offline. При такой неровной схеме эта проблема устраняется. Это конечно можно настроить в zigbee2mqtt, но я предпочел такой вариант. Сделать же период просыпания всегда раз в 3 секунды - необоснованное расходование ресурса батарейки.

**Reporting**

Модуль высылает 2 отчета для батарейки - процент заряда и напряжение. Периода отправки нет, отчет высылается по изменению. Изменение учитывает 0.1 вольт. Рабочим считается напряжение от 9.0 вольт до 7.2. Сам извещатель начиная с 7.2 вольта до 5.9 переходит в режим оповещения о разряде батареи - подает кратковременный однократный звуковой сигнал с периодомповторения от 60 до 65 секунд.

Напряжение на батарейке модуль проверяет один раз в час. Отчеты о состоянии батарейки (напряжение в мВ и остаточный ресурс в %) по изменению с шагом 0.1 вольт.


Также принудительно отчеты высылаются в течение 1 секунды, если нажать на кнопку прибора.


**Сетодиодная индикация режимов модуля**

Если модуль продолжительное время не моргает светодиодом (период более 5 минут), то он находится в режиме глубокого сна. Выйти из этого режима модуль может в двух случаях. Первый - если пользователь нажмет на кнопку. Второй - если сработает оригинальный извещатель на обнаружение дыма или если устройство снять с крепежной пластины.

1. Светодиод с периодичностью от 5 секунд до 5 минут мограет одной вспышкой - модуль находится в сети, работает в штатном режиме.
1. Светодиод с периодичностью 5 секунд моргает двумя вспышками - происходит OTA обновление прошивки.
1. Светодиод с периодичностью от 5 секунд до 5 минут моргает тремя вспышками - модуль не в сети - не был поключен, например вставили батарейки в устройство, но zigbee сети нет или активирован запрет на подключение; или был поключен, но в данный момент какие-то проблемы с сетью. В любом случае в таком режиме модуль проработает примерно 30 минут. Если за это время он не подключится к сети или не восстановит связь, то уйдет в глубокий сон. В этом режиме, чтобы связаться с модулем, нужно его разбудить, нажав на кнопку прибора.

---

**Zigbee Claster and Attribute**

В прошивке используется 1 endpoint, который содержит следующие кластеры

* Базовые кластеры.
* Кластер GEN_POWER_CFG, который отдает напряжение на батарейке и процент разряда.
* Кластер SS_IAS_ZONE, который собственно и сообщает о дыме, снятии устройства с крепежной пластины и разряженной батареи.
* Кластер GEN_ON_OFF, который посылает команду при обнаружении дыма на выбранное заранее устройство (прямой биндинг).
* Кластер ON_OFF_SWITCH_CFG, который позволяет выбрать действие кластера GEN_ON_OFF. Т.е. при обнаружении дыма возможно три варианта команды - On-Off, Off-On или Toggle.

---

## <a id="settings">Настройка</a>

Открываем на редактирование файл `configuration.yaml` от zigbee2mqtt. И добавляем в конец файла

		external_converters:
			- smoke_sensor.js
		ota:
			zigbee_ota_override_index_location: local_ota_index.json
		  
Файлы `smoke_sensor.js` и `local_ota_index.json` копируем из [репозитория проекта](https://github.com/slacky1965/smoke_sensor_zed/tree/main/zigbee2mqtt) туда же, где лежит `configuration.yaml` от zigbee2mqtt. Не забываем разрешить подключение новых устройств - `permit_join: true`. Перегружаем zigbee2mqtt. Проверяем его лог, что он запустился и нормально работает.

Далее, вставляем батарейки в устройство. Если питание было уже подано, то удерживаем кнопку на плате устройства (не на извещателе) более 5 секунд, до подтверждения сводиодом долгой вспышкой. Устройство должно подключиться к сети zigbee. Если подключение прошло удачно, то мы обнаружим наше устройство в zigbee2mqtt.

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/z2m_device.jpg"/>

После того, как устройство подключилось к сети и zigbee2mqtt его обнаружил однократно нажать на кнопку на плате устройства (не на  извещателе), для первоначального заполнения всех велечин. 

После этого можно выбрать действие для кластера OnOff. Для этого нужно перейти в web-интерфейс zigbee2mqtt и зайти в раздел exposes.

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/z2m_exposes.jpg"/>

Затем нажать кнопку на устройстве, чтобы оно проснулось и приняло данные.

**Прямой биндинг**

При срабатывании датчика, т.е. обнаружении дыма, можно послать команду OnOff на какое-то устройство (если нужно).

Для настройки прямого биндинга заходим в раздел bind устройства.

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/z2m_bind1.jpg"/>

Снимаем все галочки, оствляем только на OnOff.

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/z2m_bind2.jpg"/>

И жмем unbind, затем кнопку на плате (не на извещателе). Обновляем страницу, должно получиться вот так

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/z2m_bind3.jpg"/>

Далее в самой нижней ячейке выбираем устройство и endpoint на нем, на который хотим организвать прямую передачу команды OnOff. Ставим галочку на OnOff (выбранное устройство должно иметь такой кластер).

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/z2m_bind4.jpg"/>

Жмем bind справа и нажимаем кнопку на плате (не на извещателе). После этого обновляем страницу. Должно получиться вот так

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/z2m_bind5.jpg"/>

---

## OTA

Автоматического обновления в zigbee2mqtt для устройств, добавленных через конвертор, нет. Поэтому, если вышла новая версия, скачиваем обновленный файл прошивки для обновления OTA, например `6565-0204-13043001-smoke_sensor_zed.zigbee`. Переименовываем его в просто `smoke_sensor_zed.zigbee` и кладем его по относительному пути `zigbee2mgtt/images`. Перегружаем zigbee2mqtt. Идем во вкладку OTA. И кликаем на `Check for new updates` Если обновление принимается, то кнопка `Check for new updates` станет красной с надписью `Update device firmware`. Ее нужно кликнуть и обновление начнет загружаться (zigbee обновляется долго, что-то в районе 20 минут). 

---

## Потребление

Долгих испытаний в реальной работе пока не проводилось. С помощью ppk2 произведены замеры потребления.

**Штатный режим**

Среднее потребление за 18 минут 6.42 мкА.

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/ppk2_1.jpg"/>

**Модуль спит.**

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/ppk2_2.jpg"/>

---

## Home Assistant

В Home Assistant устройство будет выглядеть так.

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/HA_device.jpg"/>

---

## Alisa

В Яндекс устройство будет выглядеть так.

<img src="https://raw.githubusercontent.com/slacky1965/smoke_sensor_zed/main/doc/images/alisa.jpg"/>

---

P.S. 

Устройство выполнено с максимальным соблюдением zigbee стандартов. Поэтому во многих системах он будет работать, если система поддерживает стандартные кластеры, такие как OnOff и IAS. Например z2m безо вских конверторов прекрасно определяет это устройство и поддерживает IAS полностью. Яндекс так же поддерживает IAS, но не полностью, он не видит TAMPER и разряд батареи (но процент заряда через другой кластер он прекрасно видит).
