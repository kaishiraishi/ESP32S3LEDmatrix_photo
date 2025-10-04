#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// ==== ハードウェア設定 ====
#define LED_PIN   14
#define W 8
#define H 8
#define NUM_LEDS (W*H)

// NeoPixelの型（WS2812B / GRB / 800kHz）
#define PIXEL_TYPE (NEO_GRB + NEO_KHZ800)

// ==== 全体の明るさ（0–255） ====
#define GLOBAL_BRIGHTNESS  50

// 配線レイアウト：左上原点・行優先・プログレッシブ（全行同じ方向）
Adafruit_NeoMatrix matrix(
  W, H, LED_PIN,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  PIXEL_TYPE
);

// ==== 新しいテキストデータに置き換えました ====
// 64ピクセル分の [R, G, B] データ
const uint8_t imageData[NUM_LEDS][3] = {
  {124, 150, 157}, {171, 191, 192}, {155, 177, 181}, {154, 178, 185},
  {138, 170, 182}, {126, 159, 173}, {139, 167, 175}, {125, 155, 166},
  {131, 157, 163}, {130, 158, 168}, {119, 153, 167}, {149, 180, 191},
  {122, 169, 192}, {215, 224, 220}, {196, 213, 211}, {138, 171, 184},
  {128, 164, 175}, {124, 161, 174}, {173, 197, 198}, {170, 199, 207},
  {165, 192, 201}, {168, 192, 198}, {152, 181, 190}, {161, 185, 190},
  {133, 166, 173}, {110, 140, 148}, {156, 188, 196}, {164, 196, 207},
  {177, 203, 207}, {130, 153, 158}, {121, 146, 149}, {70, 84, 78},
  {83, 95, 81}, {210, 227, 210}, {44, 56, 50}, {78, 92, 86},
  {188, 178, 167}, {101, 116, 115}, {75, 90, 83}, {65, 78, 48},
  {26, 39, 21}, {11, 21, 6}, {56, 72, 42}, {61, 82, 53},
  {31, 42, 26}, {7, 19, 17}, {9, 21, 8}, {22, 33, 19},
  {137, 144, 98}, {69, 71, 59}, {155, 158, 108}, {102, 99, 79},
  {11, 18, 13}, {24, 33, 24}, {31, 33, 23}, {118, 118, 89},
  {136, 140, 96}, {154, 159, 107}, {157, 138, 112}, {119, 139, 89},
  {168, 160, 114}, {153, 153, 105}, {147, 150, 102}, {130, 132, 88}
};


void setup() {
  matrix.begin();
  matrix.setBrightness(GLOBAL_BRIGHTNESS);
  matrix.fillScreen(0); // 画面を一度クリア

  // 画像データを反時計回りに90度回転させながら描画
  for (int srcY = 0; srcY < H; srcY++) {
    for (int srcX = 0; srcX < W; srcX++) {
      // 元の画像データのインデックス
      int srcIndex = srcY * W + srcX;
      
      // 配列からR, G, Bの値を取得
      uint8_t r = imageData[srcIndex][0];
      uint8_t g = imageData[srcIndex][1];
      uint8_t b = imageData[srcIndex][2];
      
      // 反時計回りに90度回転: (srcX, srcY) → (srcY, W-1-srcX)
      int dstX = srcY;
      int dstY = W - 1 - srcX;
      
      // 回転後の座標に描画
      matrix.drawPixel(dstX, dstY, matrix.Color(r, g, b));
    }
  }
  
  // 描画内容をマトリックスに反映
  matrix.show();
}

void loop() {
  // setup()で一度描画するだけなので、loop()は空でOK
}